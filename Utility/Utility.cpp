#include "Utility.h"
#include "/opt/external-toolchain/tslib1.4/include/tslib.h"
#include <sys/fcntl.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <QDateTime>
#include <sys/utsname.h>
#include <QStringList>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

static string appFilePathSuffix()
{
    static const unsigned short s_MaxCount = 1024;
    char buf[s_MaxCount] = {'\0'};
    int ret = readlink("/proc/self/exe", buf, s_MaxCount);
    string suffix("");
    if ((ret < 0) || (ret > s_MaxCount)) {
        suffix = string("");
    } else {
        string tmp(buf);
        int pos = tmp.find_last_of(char('/'));
        if (-1 == pos) {
            suffix = string("");
        }
        suffix = tmp.substr(pos + 1, tmp.length() - 1);
    }
    return suffix;
}

bool singleApplication(const bool acquire, const std::string &key, const bool block)
{
    string app;
    if (0 == key.size()) {
        app = appFilePathSuffix();
    } else {
        app = key;
    }
    bool ret = true;
    string error;
    if (acquire) {
        error = "acquire";
    } else {
        error = "release";
    }
    if (app.empty()) {
        error = string("app is Empty!");
        ret = false;
    } else {
        string tmp = app;
        //        stringstream pidStr;
        //        pidStr << getpid();
        //        string pid;
        //        pidStr >> pid;
        tmp = string("/tmp/") + tmp;
        int fd = open(tmp.c_str(), O_RDWR | O_CREAT, 0666);
        if (fd < 0) {
            error =  string("open ") + tmp + string(" error!");
            ret = false;
        } else {
            struct flock lock;
            if (!acquire) {
                lock.l_type = F_RDLCK;
            }
            lock.l_whence = SEEK_SET;
            lock.l_start = 0;
            lock.l_len = 0;
            if ((!acquire)
                    && (0 == fcntl(fd, F_GETLK, &lock))) {
                if (F_WRLCK == lock.l_type) {
                    ret = false;
                }
            } else {
                if (acquire) {
                    lock.l_type = F_WRLCK;
                } else {
                    lock.l_type = F_UNLCK;
                }
                lock.l_pid = getpid();
                int cmd = F_SETLKW;
                if (!block) {
                    cmd = F_SETLK;
                }
                if(fcntl(fd, cmd, &lock) < 0) {
                    close(fd);
                    fd = -1;
                    error = string("application already acquire!");
                    ret = false;
                }
            }
        }
    }
    if (ret) {
        error += " success!";
    } else {
        error += " failed!";
    }
    cout << " singleApplication: " << app << " " << error << endl;
    return ret;
}

bool acquireApplication(const std::string &key, const bool block)
{
    return singleApplication(true, key, block);
}

bool releaseApplication(const std::string &key)
{
    return singleApplication(false, key, false);
}


static HANDLER m_Callback(NULL);
static void* m_Parameter(NULL);

HANDLER acquirePreemptiveResource(HANDLER callback, void *parameter)
{
    HANDLER lastHandler = m_Callback;
    if ((NULL != m_Callback) && (callback != m_Callback)) {
        m_Callback(m_Parameter);
    }
    m_Callback = callback;
    m_Parameter = parameter;
    return lastHandler;
}

void clearOwner()
{
    m_Callback = NULL;
    m_Parameter = NULL;
}

bool initializeArkVideoResources()
{
    static bool flag(false);
    if (!flag) {
        int ret = 0;
#ifndef gcc
        ret = system("./etc/memalloc_load.sh");
        ret = (0 == ret) && system("./etc/driver_load.sh");
        ret = (0 == ret) && system("./etc/itu656_load.sh");
#endif
        flag = (0 == ret);
    }
    return flag;
}
#include <fcntl.h>
bool hideArkStartupLogo()
{
    static bool flag(false);
    if (!flag) {
        int ret = 0;
#ifndef gcc
        int fd = open("/proc/display", O_WRONLY);
        if (-1 != fd) {
            const char str[] = "23";
           ret = write(fd, str, sizeof(str));
           close(fd);
           fd = -1;
        }
//        ret = system("echo 23 > /proc/display");
#endif
        flag = (3 == ret);
    }
    return flag;
}

#ifndef gcc
typedef struct {
    int x[5], xfb[5];
    int y[5], yfb[5];
    int a[7];
} calibration;

#define XORMODE	0x80000000

int perform_calibration(calibration *cal) {
    int j;
    float n, x, y, x2, y2, xy, z, zx, zy;
    float det, a, b, c, e, f, i;
    float scaling = 65536.0;

    // Get sums for matrix
    n = x = y = x2 = y2 = xy = 0;
    for(j=0;j<5;j++) {
        n += 1.0;
        x += (float)cal->x[j];
        y += (float)cal->y[j];
        x2 += (float)(cal->x[j]*cal->x[j]);
        y2 += (float)(cal->y[j]*cal->y[j]);
        xy += (float)(cal->x[j]*cal->y[j]);
    }

    // Get determinant of matrix -- check if determinant is too small
    det = n*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
    if(det < 0.1 && det > -0.1) {
        printf("ts_calibrate: determinant is too small -- %f\n",det);
        return 0;
    }

    // Get elements of inverse matrix
    a = (x2*y2 - xy*xy)/det;
    b = (xy*y - x*y2)/det;
    c = (x*xy - y*x2)/det;
    e = (n*y2 - y*y)/det;
    f = (x*y - n*xy)/det;
    i = (n*x2 - x*x)/det;

    // Get sums for x calibration
    z = zx = zy = 0;
    for(j=0;j<5;j++) {
        z += (float)cal->xfb[j];
        zx += (float)(cal->xfb[j]*cal->x[j]);
        zy += (float)(cal->xfb[j]*cal->y[j]);
    }

    // Now multiply out to get the calibration for framebuffer x coord
    cal->a[0] = (int)((a*z + b*zx + c*zy)*(scaling));
    cal->a[1] = (int)((b*z + e*zx + f*zy)*(scaling));
    cal->a[2] = (int)((c*z + f*zx + i*zy)*(scaling));

    printf("%f %f %f\n",(a*z + b*zx + c*zy),
           (b*z + e*zx + f*zy),
           (c*z + f*zx + i*zy));

    // Get sums for y calibration
    z = zx = zy = 0;
    for(j=0;j<5;j++) {
        z += (float)cal->yfb[j];
        zx += (float)(cal->yfb[j]*cal->x[j]);
        zy += (float)(cal->yfb[j]*cal->y[j]);
    }

    // Now multiply out to get the calibration for framebuffer y coord
    cal->a[3] = (int)((a*z + b*zx + c*zy)*(scaling));
    cal->a[4] = (int)((b*z + e*zx + f*zy)*(scaling));
    cal->a[5] = (int)((c*z + f*zx + i*zy)*(scaling));

    printf("%f %f %f\n",(a*z + b*zx + c*zy),
           (b*z + e*zx + f*zy),
           (c*z + f*zx + i*zy));

    // If we got here, we're OK, so assign scaling to a[6] and return
    cal->a[6] = (int)scaling;
    return 1;
    /*
// This code was here originally to just insert default values
    for(j=0;j<7;j++) {
        c->a[j]=0;
    }
    c->a[1] = c->a[5] = c->a[6] = 1;
    return 1;
*/

}

static int sort_by_x(const void* a, const void *b)
{
    return (((struct ts_sample *)a)->x - ((struct ts_sample *)b)->x);
}

static int sort_by_y(const void* a, const void *b)
{
    return (((struct ts_sample *)a)->y - ((struct ts_sample *)b)->y);
}

void getxy(struct tsdev *ts, int *x, int *y)
{
#define MAX_SAMPLES 128
    struct ts_sample samp[MAX_SAMPLES];
    int index, middle;

    do {
        if (ts_read_raw(ts, &samp[0], 1) < 0) {
            perror("ts_read");
//            close_framebuffer ();
            exit(1);
        }

    } while (samp[0].pressure == 0);

    /* Now collect up to MAX_SAMPLES touches into the samp array. */
    index = 0;
    do {
        if (index < MAX_SAMPLES-1)
            index++;
        if (ts_read_raw(ts, &samp[index], 1) < 0) {
            perror("ts_read");
//            close_framebuffer ();
            exit(1);
        }
    } while (samp[index].pressure > 0);
    printf("Took %d samples...\n",index);

    /*
     * At this point, we have samples in indices zero to (index-1)
     * which means that we have (index) number of samples.  We want
     * to calculate the median of the samples so that wild outliers
     * don't skew the result.  First off, let's assume that arrays
     * are one-based instead of zero-based.  If this were the case
     * and index was odd, we would need sample number ((index+1)/2)
     * of a sorted array; if index was even, we would need the
     * average of sample number (index/2) and sample number
     * ((index/2)+1).  To turn this into something useful for the
     * real world, we just need to subtract one off of the sample
     * numbers.  So for when index is odd, we need sample number
     * (((index+1)/2)-1).  Due to integer division truncation, we
     * can simplify this to just (index/2).  When index is even, we
     * need the average of sample number ((index/2)-1) and sample
     * number (index/2).  Calculate (index/2) now and we'll handle
     * the even odd stuff after we sort.
     */
    middle = index/2;
    if (x) {
        qsort(samp, index, sizeof(struct ts_sample), sort_by_x);
        if (index & 1)
            *x = samp[middle].x;
        else
            *x = (samp[middle-1].x + samp[middle].x) / 2;
    }
    if (y) {
        qsort(samp, index, sizeof(struct ts_sample), sort_by_y);
        if (index & 1)
            *y = samp[middle].y;
        else
            *y = (samp[middle-1].y + samp[middle].y) / 2;
    }
}

static void get_sample (struct tsdev *ts, calibration *cal,
                        int index, int x, int y, char *name)
{
    static int last_x = -1, last_y;

    if (last_x != -1) {
#define NR_STEPS 10
        int dx = ((x - last_x) << 16) / NR_STEPS;
        int dy = ((y - last_y) << 16) / NR_STEPS;
        int i;
        last_x <<= 16;
        last_y <<= 16;
        for (i = 0; i < NR_STEPS; i++) {
//            put_cross (last_x >> 16, last_y >> 16, 2 | XORMODE);
            usleep (1000);
//            put_cross (last_x >> 16, last_y >> 16, 2 | XORMODE);
            last_x += dx;
            last_y += dy;
        }
    }

//    put_cross(x, y, 2 | XORMODE);
    getxy (ts, &cal->x [index], &cal->y [index]);
//    put_cross(x, y, 2 | XORMODE);

    last_x = cal->xfb [index] = x;
    last_y = cal->yfb [index] = y;

    printf("%s : X = %4d Y = %4d\n", name, cal->x [index], cal->y [index]);
}
#endif

void startCalibratre()
{
#ifndef gcc
    struct tsdev *ts;
    calibration cal;
    int cal_fd;
    char cal_buffer[256];
    char *tsdevice = NULL;
    char *calfile = NULL;
    unsigned int i;
    if( (tsdevice = getenv("TSLIB_TSDEVICE")) != NULL ) {
        ts = ts_open(tsdevice,0);
        printf("TSLIB_TSDEVICE");
    } else {
#ifdef USE_INPUT_API
        ts = ts_open("/dev/input/event0", 0);
        printf("/dev/input/event0");
#else
        ts = ts_open("/dev/touchscreen/ucb1x00", 0);
        printf("/dev/touchscreen/ucb1x00");
#endif /* USE_INPUT_API */
    }

    if (!ts) {
        perror("ts_open");
        exit(1);
    }
    if (ts_config(ts)) {
        perror("ts_config");
        exit(1);
    }
    int xres(1280);
    int yres(720);
    get_sample (ts, &cal, 0, 50,        50,        "Top left");
    printf("Top left");
    get_sample (ts, &cal, 1, xres - 50, 50,        "Top right");
    printf("Top right");
    get_sample (ts, &cal, 2, xres - 50, yres - 50, "Bot right");
    printf("Bot right");
    get_sample (ts, &cal, 3, 50,        yres - 50, "Bot left");
    printf("Bot left");
    get_sample (ts, &cal, 4, xres / 2,  yres / 2,  "Center");
    printf("Center");

    if (perform_calibration (&cal)) {
        printf ("Calibration constants: ");
        for (i = 0; i < 7; i++) printf("%d ", cal.a [i]);
        printf("\n");
        if ((calfile = getenv("TSLIB_CALIBFILE")) != NULL) {
            cal_fd = open (calfile, O_CREAT | O_RDWR);
        } else {
            cal_fd = open ("/etc/pointercal", O_CREAT | O_RDWR);
        }
        sprintf (cal_buffer,"%d %d %d %d %d %d %d",
                 cal.a[1], cal.a[2], cal.a[0],
                cal.a[4], cal.a[5], cal.a[3], cal.a[6]);
        write (cal_fd, cal_buffer, strlen (cal_buffer) + 1);
        close (cal_fd);
        i = 0;
    } else {
        printf("Calibration failed.\n");
        i = -1;
    }
#endif
}

const QString compilerDate()
{
    char month[4] = {0};
    int MM, dd, yyyy;
    struct tm t = {0};
    static const char monthNames[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
    sscanf(__DATE__, "%s %d %d", month, &dd, &yyyy);
    MM = (strstr(monthNames, month) - monthNames) / 3;
    t.tm_year = yyyy - 1900;
    t.tm_mday = dd;
    t.tm_mon = MM;
    return QDateTime::fromTime_t((uint)mktime(&t)).toString("yyyy-MM-dd");
}

const QString osVersion()
{
    QString version/*("#210 Mon Jun 12 11:40:05 CST 2017")*/;
    struct utsname  kernelInfo;
    if (uname(&kernelInfo) != -1) {
        version = QString(kernelInfo.version);
    }
    QString year, month, day;
    QStringList stringList = version.split(QChar(' '));
    for (int i = 0; i < stringList.size(); ++i) {
#ifndef gcc
        if (2 == i) {
#else
        if (3 == i) {
#endif
            month = stringList.at(i);
            if (month.contains("Jan")) {
                month = QString("01");
            } else if (month.contains("Feb")) {
                month = QString("02");
            } else if (month.contains("Mar")) {
                month = QString("03");
            } else if (month.contains("Apr")) {
                month = QString("04");
            } else if (month.contains("May")) {
                month = QString("04");
            } else if (month.contains("Jun")) {
                month = QString("06");
            } else if (month.contains("Jul")) {
                month = QString("07");
            } else if (month.contains("Aug")) {
                month = QString("08");
            } else if (month.contains("Sep")) {
                month = QString("09");
            } else if (month.contains("Oct")) {
                month = QString("10");
            } else if (month.contains("Nov")) {
                month = QString("11");
            } else /*if (month.contains("Dec"))*/ {
                month = QString("12");
            }
#ifndef gcc
        } else if (3 == i) {
#else
        } else if (4 == i) {
#endif
            day = stringList.at(i);
        } else if (i == stringList.size() - 1) {
            year = stringList.at(i);
        }
    }
    return year + QString("-") + month + QString("-") + day;
}
