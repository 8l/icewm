
<<<<<<< HEAD
#if defined(linux) || (defined (__FreeBSD__)) || (defined(__NetBSD__) && defined(i386))
=======
#if defined(linux) || (defined (__FreeBSD__)) || (defined (__FreeBSD_kernel__))  || (defined(__NetBSD__) && defined(i386))
>>>>>>> a2d63443c9ab57fa6a436e3d505b6bd708dfc8a4

#include "ywindow.h"
#include "ytimer.h"

<<<<<<< HEAD
#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
=======
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__)
>>>>>>> a2d63443c9ab57fa6a436e3d505b6bd708dfc8a4
#define APMDEV "/dev/apm"
#else
#define APMDEV "/proc/apm"
#endif

//assume there is no laptop with more
//than 3 batteries
#define MAX_ACPI_BATTERY_NUM 3

typedef struct {
  //(file)name of battery
  int present;
  char *name;
  int capacity_full;
} bat_info;


class YApm: public YWindow, public YTimerListener {
public:
    YApm(YWindow *aParent = 0);
    virtual ~YApm();

    virtual void paint(Graphics &g, const YRect &r);

    void updateToolTip();
    virtual bool handleTimer(YTimer *t);

private:
    YTimer *apmTimer;

    ref<YPixmap> getPixmap(char ch);
    int calcInitialWidth();
    int calcWidth(const char *s, int count);

    void AcpiStr(char *s, bool Tool);
    void SysStr(char *s, bool Tool);
    void PmuStr(char *, const bool);
    void ApmStr(char *s, bool Tool);
    int ignore_directory_bat_entry(struct dirent *de);
    int ignore_directory_ac_entry(struct dirent *de);

    static YColor *apmBg;
    static YColor *apmFg;
    static ref<YFont> apmFont;

    static YColor *apmColorOnLine;
    static YColor *apmColorBattery;
    static YColor *apmColorGraphBg;

    // display mode: pmu, acpi or apm info
    enum { APM, ACPI, PMU, SYSFS } mode;
    //number of batteries (for apm == 1)
    int batteryNum;
    //names of batteries to ignore. e.g.
    //the laptop has two slots but the
    //user has only one battery
    static char *acpiIgnoreBatteryNames;
    //list of batteries (static info)
    bat_info *acpiBatteries[MAX_ACPI_BATTERY_NUM];
    //(file)name of ac adapter
    char *acpiACName;
    char *fCurrentState;

    // On line status and charge persent
    int      acIsOnLine;
    double   chargeStatus;

    void updateState();
};
#else
#undef CONFIG_APPLET_APM
#endif
