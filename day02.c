
<!-- saved from url=(0127)http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7 -->
<html xmlns="http://www.w3.org/1999/xhtml"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>COOKBOOK</title>
    
    <script type="text/javascript" src="jquery.min.js">
    </script>
    <script type="text/javascript" src="jquery.snippet.js">
    </script>
    <script type="text/javascript" src="index.js">
    </script>
    <link type="text/css" href="index.css" rel="Stylesheet">
    <link type="text/css" href="jquery.snippet.css" rel="Stylesheet">
  </head>
  <body>
    <h1>嵌入式驱动程序Day02</h1>
    <a id="linkTop" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">Top</a>
    <ol class="index">
      <li>
        <a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#case1">按键驱动 V 1.1</a>
      </li>
      <li>
        <a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#case2">按键驱动 V 1.2</a>
      </li>
      <li>
        <a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#case3">按键驱动 V 1.3</a>
      </li>
      <li>
        <a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#case4">按键驱动 V 1.4</a>
      </li>
      <li>
        <a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#case5">按键驱动 V 1.5</a>
      </li>
      <li>
        <a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#case6">多个设备个体实验</a>
      </li>
    </ol>
    <a name="case1">
    </a>
    <h2>1 按键驱动 V 1.1</h2>
    <h3>1.1 问题</h3>
    <p>在按键驱动程序中，为按键分别采用静态和动态的方式为设备申请主设备号。</p>
    <h3>1.2 方案</h3>
    <p class="number">一、静态和动态方式主设备号。</p>
    <p>一个字符设备或者块设备都有一个主设备号和次设备号。主设备号和次设备号统称为设备号。主设备号用来表示一个特定的驱动程序。次设备号用来表示使用该驱动程序的各设备。在Linux内核中，dev_t类型用来表示设备号。以32位机为例，其中高12表示主设备号，低20为表示次设备号。</p>
    <p>有两种方式来获得设备号，分别是静态分别设备号，动态分配设备号。</p>
    <p class="number">1.静态分配设备号。</p>
    <p>静态分配设备号，就是驱动程序开发者，静态地指定一个设备号。对于一部分常用的设备，内核开发者已经为其分配了设备号。这些设备号可以在内核源码Documentation/ devices.txt文件中找到。如果只有开发者自己使用这些设备驱动程序，那么其可以选择一个尚未使用的设备号。在不添加新硬件的时候，这种方式不会产生设备号冲突。但是当添加新硬件时，则很可能造成设备号冲突，影响设备的使用。静态申请设备号的函数是register_chrdev_region（）。其原型是：</p>
    <p>int register_chrdev_region(dev_t first, unsigned int count, const char *name);</p>
    <p>参数 first： 表示起始设备号；</p>
    <p>参数 count：  表示从起始设备号开始连续的设备号数目，需要注意的是 count 不能过大，不然有可能溢出到下一个主设备号上；</p>
    <p>参数 name： 表示设备的名称，这个名称也会在 /proc/devices 文件以及sfsfs 中看到。register_chrdev_region（）成功时返回 0 ，失败时返回负数。register_chrdev_region（）函数用于已知起始设备的设备号的情况。</p>
    <p class="number">2.动态分配设备号。</p>
    <p>由于静态分配设备号存在冲突的问题，所以内核社区建议开发者使用动态分配设备号的方法。动态分配设备号的函数是alloc_chrdev_region（）。其原型是：</p>
    <p>int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, const char *name);</p>
    <p>参数 dev：在系统调用成功后，会把得到的设备号放到这个参数中；</p>
    <p>参数 firstminor： 是请求的第一个次设备号，一般为 0 ；</p>
    <p>参数 count：表示一个范围值；</p>
    <p>参数 name：表示设备名。</p>
    <p>alloc_chrdev_region() 用于设备号未知，向系统动态申请未被占用的设备号情况。</p>
    <p class="number">二、本案例的操作步骤如下。</p>
    <p class="number">1.使用静态方式申请主设备号。</p>
    <p>（1）编写chardevicedriver.c源文件，使用静态方式申请设备号；</p>
    <p>1）包含相对应使用到的头文件；</p>
    <p>2）定义四个宏分别表示主设备号CHARDEVICEDRIVER_MAJOR为240，次设备号CHARDEVICEDRIVER_MINOR为0，设备个数CHARDEVICEDRIVER_COUNT为1，设备名字CHARDEVICEDRIVER_NAME为chardevicedriver;</p>
    <p>3）编写chardevicedriver_init（）函数，在此函数中定义一个设备号类型的变量dev，使用MKDEV（）宏生成设备的设备号，再使用register_chrdev_region（）函数静态申请该设备号；</p>
    <p>4）编写chardevicedriver_exit（）函数，在此函数中中使用unregister_chrdev_region（）函数来注销设备的设备号；</p>
    <p>5）使用宏module_init（）和宏module_exit（）来分别注册chardevicedriver_init（）函数和chardevicedriver_exit（）函数;</p>
    <p>（2）编写Makefile文件；</p>
    <p>（3）编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko拷贝到指定目录 ；</p>
    <p>（4）重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p class="number">2.使用动态方式申请主设备号。</p>
    <p>（1）编写chardevicedriver.c源文件，使用动态方式申请设备号；</p>
    <p>1）在chardevicedriver_init（）函数中使用alloc_chrdev_region（）函数来实现动态申请设备号；</p>
    <p>2）在chardevicedriver_exit（）函数中使用unregister_chrdev_region（）函数来注销设备号；</p>
    <p>（2）编写Makefile文件；</p>
    <p>（3）编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko拷贝到指定目录 ；</p>
    <p>（4）重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <h3>1.3 实现</h3>
    <p class="number">1.编写chardevicedriver.c源文件，在chardevicedriver_init函数中使用register_chrdev_region（）来实现静态申请设备号。</p>
    <p class="number">步骤1：编辑chardevicedriver.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style=""><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下，隐藏代码部分为需要添加的代码：</p>
    <p>编写该源代码之前，先查阅内核源码的Documentation/devices.txt文件，确定将要申请的主设备号240并未被其他设备使用，因此，我们向系统申请240为该设备的主设备号。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">240</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">1</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">,</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">register_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: </span><span class="sh_specialchar">\n</span><span class="sh_string">Device Major = %d</span><span class="sh_specialchar">\n</span><span class="sh_string"> Device Minor = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">,</span>CHARDEVICEDRIVER_MINOR<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">,</span> CHARDEVICEDRIVER_MINOR <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Exit chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;asm/uaccess.h&gt;
#include &lt;linux/gpio.h&gt;

MODULE_LICENSE("Dual BSD/GPL");
#define CHARDEVICEDRIVER_MAJOR		240
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		1
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"

// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

	// register device number
	dev = MKDEV( CHARDEVICEDRIVER_MAJOR, CHARDEVICEDRIVER_MINOR);
	ret = register_chrdev_region( dev, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", CHARDEVICEDRIVER_MAJOR);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: \nDevice Major = %d\n Device Minor = %d\n", CHARDEVICEDRIVER_MAJOR,CHARDEVICEDRIVER_MINOR);

failure_register_chrdev:
	return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");

// unregister device number
	unregister_chrdev_region( MKDEV( CHARDEVICEDRIVER_MAJOR, CHARDEVICEDRIVER_MINOR ), CHARDEVICEDRIVER_COUNT );
	printk(KERN_ALERT "CharDeviceDriver: Exit chardevicedriver_exit !\n");
}

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">步骤2：编写Makefile文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style=""><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li># makefile <span class="sh_keyword">for</span> kernel module</li><li><span style="display:none;">&nbsp;</span></li><li>MODNAME <span class="sh_symbol">=</span> chardevicedriver</li><li>CROSS_COMPILE <span class="sh_symbol">=</span> arm<span class="sh_symbol">-</span>linux<span class="sh_symbol">-</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">ifeq</span> <span class="sh_symbol">(</span>$<span class="sh_symbol">(</span>PLATFORM<span class="sh_symbol">),</span> PC<span class="sh_symbol">)</span></li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>lib<span class="sh_symbol">/</span>modules<span class="sh_symbol">/</span>$<span class="sh_symbol">(</span><span class="sh_usertype">shell</span><span class="sh_normal"> </span>uname <span class="sh_symbol">-</span>r<span class="sh_symbol">)/</span>build</li><li><span class="sh_keyword">else</span></li><li>CC <span class="sh_symbol">=</span> $<span class="sh_symbol">(</span>CROSS_COMPILE<span class="sh_symbol">)</span>gcc</li><li>KERNELDIR <span class="sh_symbol">?=</span>  <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>tools<span class="sh_symbol">/</span>linux<span class="sh_number">-2.6.35.7</span></li><li>endif</li><li><span style="display:none;">&nbsp;</span></li><li>obj<span class="sh_symbol">-</span>m <span class="sh_symbol">:=</span> $<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>o</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">default</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>MAKE<span class="sh_symbol">)</span> <span class="sh_symbol">-</span>C $<span class="sh_symbol">(</span>KERNELDIR<span class="sh_symbol">)</span> M<span class="sh_symbol">=</span>$<span class="sh_symbol">(</span>PWD<span class="sh_symbol">)</span> modules</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>clean<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>rf <span class="sh_symbol">*.</span>o <span class="sh_symbol">*.</span>ko <span class="sh_symbol">*.</span>mod<span class="sh_symbol">.*</span> <span class="sh_symbol">.</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).*</span> <span class="sh_symbol">.</span>tmp<span class="sh_symbol">*</span> module<span class="sh_symbol">*</span> Module<span class="sh_symbol">*</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;"># makefile for kernel module

MODNAME = chardevicedriver
CROSS_COMPILE = arm-linux-

ifeq ($(PLATFORM), PC)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
else
CC = $(CROSS_COMPILE)gcc
KERNELDIR ?=  /home/tarena/workdir/tools/linux-2.6.35.7
endif

obj-m := $(MODNAME).o

default:
	@echo "Compiling device driver..."
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@echo

clean:
	@echo "Cleanup device driver..."
	@rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
	@echo
</pre></div></div>
    <p class="number">步骤3：编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko文件拷贝到指定目录下，执行如下命令:</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span>ko   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">步骤4：重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#   <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li><li><span class="sh_symbol">/</span>#   rmmod    chardevicedriver </li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#   insmod   chardevicedriver.ko
/#   rmmod    chardevicedriver 
</pre></div></div>
    <p>如图-1所示，向系统申请静态的设备号为主设备号为240，次设备号为0。，如图-2所示，为注销该设备号。</p>
    <div class="image">
      <img src="image001.png">
      <p>图-1</p>
    </div>
    <div class="image">
      <img src="image002.png">
      <p>图-2</p>
    </div>
    <p class="number">2.编写chardevicedriver.c源文件，在chardevicedriver_init函数中使用alloc_chrdev_region（）函数来实现动态申请设备号。</p>
    <p class="number">步骤1：编辑chardevicedriver.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下，隐藏代码部分为需要添加的代码：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_comment">// include kernel head files</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span class="sh_comment">// licensed under BSD/GPL</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">1</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_major <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_minor <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// dynamic device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">alloc_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>dev<span class="sh_symbol">,</span> chardevicedriver_minor<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_major <span class="sh_symbol">=</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: </span><span class="sh_specialchar">\n</span><span class="sh_string">Device Major = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">Device Minor = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">,</span>chardevicedriver_minor<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">// include kernel head files
#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;linux/uaccess.h&gt;
#include &lt;linux/gpio.h&gt;
// licensed under BSD/GPL
MODULE_LICENSE("Dual BSD/GPL");

#define CHARDEVICEDRIVER_MAJOR		0
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		1
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"

static u32 chardevicedriver_major = CHARDEVICEDRIVER_MAJOR;
static u32 chardevicedriver_minor = CHARDEVICEDRIVER_MINOR;

// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

 
	// dynamic device number
	ret = alloc_chrdev_region( &amp;dev, chardevicedriver_minor, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	chardevicedriver_major = MAJOR( dev );
	
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", chardevicedriver_major);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: \nDevice Major = %d\nDevice Minor = %d\n", chardevicedriver_major,chardevicedriver_minor);

	return ret;

failure_register_chrdev:
	return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");

	// unregister device number
	unregister_chrdev_region( MKDEV( chardevicedriver_major, chardevicedriver_minor ), CHARDEVICEDRIVER_COUNT );
}

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");

</pre></div></div>
    <p class="number">步骤2：编写Makefile文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li># makefile <span class="sh_keyword">for</span> kernel module</li><li><span style="display:none;">&nbsp;</span></li><li>MODNAME <span class="sh_symbol">=</span> chardevicedriver</li><li>CROSS_COMPILE <span class="sh_symbol">=</span> arm<span class="sh_symbol">-</span>linux<span class="sh_symbol">-</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">ifeq</span> <span class="sh_symbol">(</span>$<span class="sh_symbol">(</span>PLATFORM<span class="sh_symbol">),</span> PC<span class="sh_symbol">)</span></li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>lib<span class="sh_symbol">/</span>modules<span class="sh_symbol">/</span>$<span class="sh_symbol">(</span><span class="sh_usertype">shell</span><span class="sh_normal"> </span>uname <span class="sh_symbol">-</span>r<span class="sh_symbol">)/</span>build</li><li><span class="sh_keyword">else</span></li><li>CC <span class="sh_symbol">=</span> $<span class="sh_symbol">(</span>CROSS_COMPILE<span class="sh_symbol">)</span>gcc</li><li>KERNELDIR <span class="sh_symbol">?=</span>  <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>tools<span class="sh_symbol">/</span>linux<span class="sh_number">-2.6.35.7</span></li><li>endif</li><li><span style="display:none;">&nbsp;</span></li><li>obj<span class="sh_symbol">-</span>m <span class="sh_symbol">:=</span> $<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>o</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">default</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>MAKE<span class="sh_symbol">)</span> <span class="sh_symbol">-</span>C $<span class="sh_symbol">(</span>KERNELDIR<span class="sh_symbol">)</span> M<span class="sh_symbol">=</span>$<span class="sh_symbol">(</span>PWD<span class="sh_symbol">)</span> modules</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>clean<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>rf <span class="sh_symbol">*.</span>o <span class="sh_symbol">*.</span>ko <span class="sh_symbol">*.</span>mod<span class="sh_symbol">.*</span> <span class="sh_symbol">.</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).*</span> <span class="sh_symbol">.</span>tmp<span class="sh_symbol">*</span> module<span class="sh_symbol">*</span> Module<span class="sh_symbol">*</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;"># makefile for kernel module

MODNAME = chardevicedriver
CROSS_COMPILE = arm-linux-

ifeq ($(PLATFORM), PC)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
else
CC = $(CROSS_COMPILE)gcc
KERNELDIR ?=  /home/tarena/workdir/tools/linux-2.6.35.7
endif

obj-m := $(MODNAME).o

default:
	@echo "Compiling device driver..."
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@echo

clean:
	@echo "Cleanup device driver..."
	@rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
	@echo
</pre></div></div>
    <p class="number">步骤3：编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko文件拷贝到指定目录下，执行如下命令:</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span>ko   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">步骤4：重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#   <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li><li><span class="sh_symbol">/</span>#   rmmod    chardevicedriver </li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#   insmod   chardevicedriver.ko
/#   rmmod    chardevicedriver 
</pre></div></div>
    <p>如图-3所示，系统为设备自动分配的设备号为主设备号为251，次设备号为0。如图-4所示，为注销该设备号。</p>
    <div class="image">
      <img src="image003.png">
      <p>图-3</p>
    </div>
    <div class="image">
      <img src="image004.png">
      <p>图-4</p>
    </div>
    <h3>1.4 扩展</h3>
    <a name="case2">
    </a>
    <h2>2 按键驱动 V 1.2</h2>
    <h3>2.1 问题</h3>
    <p>在为按键申请设备号成功的基础上，实现向内核注册按键驱动程序。</p>
    <h3>2.2 方案</h3>
    <p class="number">一、如何向内核注册设备驱动程序。</p>
    <p>在 linux 2.6内核中，使用 cdev结构体描述字符设备，cdev 的定义在 &lt;linux/cdev.h&gt; 中可找到，其定义如下：</p>
    <p>struct cdev {</p>
    <p>struct  kobject  kobj;</p>
    <p>struct  module  *owner;</p>
    <p>const  struct  file_operations  *ops;</p>
    <p>struct  list_head  list;</p>
    <p>dev_t   dev;</p>
    <p>unsigned  int  count;</p>
    <p>};</p>
    <p>其中，struct kobject 是内嵌的 kobject 对象；</p>
    <p>struct module 是所属模块；</p>
    <p>struct file_operations是操纵这个字符设备文件的方法集合。</p>
    <p>dev_t 成员定义了设备号，为 32 位，其中高 12 位为主设备号，低 20 位为次设备号。</p>
    <p>使用以下宏可以从 dev_t 获得主设备号和次设备号：</p>
    <p>MAJOR (dev_t dev);</p>
    <p>MINOR (dev_t dev);</p>
    <p>而使用下面宏可以通过主设备号和次设备号生成 dev_t&nbsp; ：</p>
    <p>MKDEV (int major, int minor);</p>
    <p>有时可能希望就把 cdev 结构内嵌在自己的特定设备结构里，那么在分配好 cdev 结构后，就用 cdev_init() 函数对其初始化：</p>
    <p>void cdev_init (struct cdev *cdev, struct file_operations *fops)</p>
    <p>cdev_init() 函数代码为：</p>
    <p>void cdev_init(struct cdev *cdev, const struct file_operations *fops){</p>
    <p>memset(cdev, 0, sizeof *cdev);</p>
    <p>INIT_LIST_HEAD(&amp;cdev-&gt;list);</p>
    <p>kobject_init(&amp;cdev-&gt;kobj, &amp;ktype_cdev_default);</p>
    <p>cdev-&gt;ops = fops;</p>
    <p>}</p>
    <p>另外，像 cdev 中的 owner 要设置为 THIS_MOULE 。</p>
    <p>一旦 cdev 结构体设置完毕，最后一步就是要把这事告诉给内核，使用下面的函数：int cdev_add(struct cdev *p, dev_t dev, unsigned count)</p>
    <p>cdev_add() 对应的代码为：</p>
    <p>int cdev_add(struct cdev *p, dev_t dev, unsigned count)</p>
    <p>{</p>
    <p>p-&gt;dev = dev;</p>
    <p>p-&gt;count = count;</p>
    <p>return kobj_map(cdev_map, dev, count, NULL, exact_match, exact_lock, p);</p>
    <p>}</p>
    <p>参数 p： 是 cdev 结构体的指针；</p>
    <p>参数 dev： 是设备响应的第一个设备号；</p>
    <p>参数 count： 和设备相关联的设备号的数目。</p>
    <p>一般的，count 的值为 1，但是有些情形也可能是大于 1 的数。比如 SCSI 磁带机，它通过给每个物理设备安排多个此设备号来允许用户在应用程序里选择操作模式(比如密度)。</p>
    <p>对系统而言，当设备驱动程序成功调用了cdev_add之后，就意味着一个字符设备对象已经加入到了系统，设备也就 “活” 了起来，于是所对应的操作方法(file_operations 结构里所定义的各种函数)也就能为内核所调用。对用户态的程序而言，cdev_add调用之后，就已经可以通过文件系统的接口使用我们的驱动程序了。</p>
    <p>cdev_add 如果失败了，那么返回一个负值，表明驱动无法加载到系统中，然而它一般情况下都会成功。</p>
    <p>从系统中移除一个字符设备，可以调用以下函数：</p>
    <p>void cdev_del(struct cdev *p) 。</p>
    <p class="number">二、本案例的操作步骤如下。</p>
    <p class="number">1.编写chardevicedriver.c源文件。</p>
    <p>（1）定义主设备变量chardevicedriver_major为0，定义次设备号变量chardevicedriver_minor为0；</p>
    <p>（2）定义设备结构体类型cdev的变量chardevicedriver_cdev;</p>
    <p>（3）实现函数chardevicedriver_open（）和chardevicedriver_release（）两个函数；</p>
    <p>（4）定义file_operations结构体 chardevicedriver_fops，将实现了的chardevicedriver_open（），chardevicedriver_release（）两个函数赋值给结构体chardevicedriver_fops中的open和release两接口；</p>
    <p>（5）在chardevicedriver_init（）函数中使用memset（）函数为设备结构体变量chardevicedriver_cdev所分配到的内存空间初始化为0；</p>
    <p>（6）在chardevicedriver_init（）函数中使用cdev_init（）函数实现对chardevicedriver_cdev的初始化，特别是将chardevicedriver_fops驱动操作函数结构体赋值给该设备结构体；</p>
    <p>（7）在chardevicedriver_init（）函数中使用cdev_add（）函数实现将chardevicedriver_cdev设备结构体添加到内核；</p>
    <p>（8）在chardevicedriver_exit（）函数中使用cdev_del（）函数实现从系统中删除chardevicedriver_cdev设备结构体；</p>
    <p class="number">2.编写testchardevicedriver.c源文件。</p>
    <p class="number">3.编写Makefile文件。</p>
    <p class="number">4.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko拷贝到指定目录 。</p>
    <p class="number">5.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p class="number">6.根据动态分配的主次设备号，手动创建设备文件节点。</p>
    <p class="number">7.运行应用测试程序，测试驱动程序。</p>
    <h3>2.3 实现</h3>
    <p class="number">1.编写chardevicedriver.c源文件，在chardevicedriver_init函数中使用cdev_init()和cdev_add()函数来实现注册设备驱动。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span class="sh_comment">// licensed under BSD/GPL</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">1</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_major <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_minor <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> struct <span class="sh_usertype">cdev</span><span class="sh_normal"> </span>chardevicedriver_cdev<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_open</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardeivcedriver_open !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_release</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_release !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file_operations</span><span class="sh_normal"> </span>chardevicedriver_fops <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>owner&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> THIS_MODULE<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>open&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_open<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>release<span class="sh_symbol">=</span> chardevicedriver_release<span class="sh_symbol">,</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> chardevicedriver_major <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// static device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">register_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">else</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// dynamic device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">alloc_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>dev<span class="sh_symbol">,</span> chardevicedriver_minor<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_major <span class="sh_symbol">=</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>      chardevicedriver_minor <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: Device Major = %d;Device Minor = %d!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">,</span>chardevicedriver_minor<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">memset</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev<span class="sh_symbol">,</span> <span class="sh_number">0</span><span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>cdev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_init</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>chardevicedriver_fops <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">cdev_add</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev<span class="sh_symbol">,</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Failure to add cdev to kernel, return value = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> ret<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_add_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to add cdev to kernel !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_add_cdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// delete cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_del</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;linux/uaccess.h&gt;
#include &lt;linux/gpio.h&gt;
// licensed under BSD/GPL
MODULE_LICENSE("Dual BSD/GPL");

#define CHARDEVICEDRIVER_MAJOR		0
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		1
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"

static u32 chardevicedriver_major = CHARDEVICEDRIVER_MAJOR;
static u32 chardevicedriver_minor = CHARDEVICEDRIVER_MINOR;

static struct cdev chardevicedriver_cdev;

static int chardevicedriver_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardeivcedriver_open !\n");

	return 0;
}

static int chardevicedriver_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_release !\n");

	return 0;
}

static struct file_operations chardevicedriver_fops = {
	.owner	= THIS_MODULE,
	.open	= chardevicedriver_open,
	.release= chardevicedriver_release,
};

// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

	// register device number
	if( chardevicedriver_major ) { // static device number
		dev = MKDEV( chardevicedriver_major, chardevicedriver_minor );
		ret = register_chrdev_region( dev, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	}
	else { // dynamic device number
		ret = alloc_chrdev_region( &amp;dev, chardevicedriver_minor, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
		chardevicedriver_major = MAJOR( dev );
      chardevicedriver_minor = MINOR( dev );
	}
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", chardevicedriver_major);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: Device Major = %d;Device Minor = %d!\n", chardevicedriver_major,chardevicedriver_minor);

	// register cdev object
	memset( &amp;chardevicedriver_cdev, 0, sizeof( struct cdev ) );
	cdev_init( &amp;chardevicedriver_cdev, &amp;chardevicedriver_fops );
	ret = cdev_add( &amp;chardevicedriver_cdev, dev, CHARDEVICEDRIVER_COUNT );
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Failure to add cdev to kernel, return value = %d !\n", ret);
		goto failure_add_cdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to add cdev to kernel !\n");

	return ret;

failure_add_cdev:
	unregister_chrdev_region( dev, CHARDEVICEDRIVER_COUNT );
failure_register_chrdev:
	return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");
	// delete cdev object
	cdev_del( &amp;chardevicedriver_cdev );
	// unregister device number
	unregister_chrdev_region( MKDEV( chardevicedriver_major, chardevicedriver_minor ), CHARDEVICEDRIVER_COUNT );

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">2.编写testchardevicedriver.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>stdio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>stdlib<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>fcntl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> fd<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">(</span><span class="sh_type">int</span> argc<span class="sh_symbol">,</span> <span class="sh_type">char</span> <span class="sh_symbol">**</span>argv<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>       fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Failure to open device file: /dev/chardevicedriver!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">exit</span><span class="sh_symbol">(</span> <span class="sh_symbol">-</span><span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to open device file: /dev/chardevicedriver !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li> &nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">close</span><span class="sh_symbol">(</span> fd <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to test device: /dev/chardevicedriver !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;

int fd;

int main(int argc, char **argv)
{
       fd = open( "/dev/chardevicedriver", O_RDWR );

	if( 0 &gt; fd ) {
		printf("Failure to open device file: /dev/chardevicedriver!\n");
		exit( -1 );
	}
	printf("Success to open device file: /dev/chardevicedriver !\n");

 	close( fd );
	printf("Success to test device: /dev/chardevicedriver !\n");

	return 0;
}
</pre></div></div>
    <p class="number">3.编写Makefile文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li># makefile <span class="sh_keyword">for</span> kernel module</li><li><span style="display:none;">&nbsp;</span></li><li>MODNAME <span class="sh_symbol">=</span> chardevicedriver</li><li>CROSS_COMPILE <span class="sh_symbol">=</span> arm<span class="sh_symbol">-</span>linux<span class="sh_symbol">-</span></li><li>TESTPRE&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> test</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">ifeq</span> <span class="sh_symbol">(</span>$<span class="sh_symbol">(</span>PLATFORM<span class="sh_symbol">),</span> PC<span class="sh_symbol">)</span></li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>lib<span class="sh_symbol">/</span>modules<span class="sh_symbol">/</span>$<span class="sh_symbol">(</span><span class="sh_usertype">shell</span><span class="sh_normal"> </span>uname <span class="sh_symbol">-</span>r<span class="sh_symbol">)/</span>build</li><li><span class="sh_keyword">else</span></li><li>CC <span class="sh_symbol">=</span> $<span class="sh_symbol">(</span>CROSS_COMPILE<span class="sh_symbol">)</span>gcc</li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>tools<span class="sh_symbol">/</span>linux<span class="sh_number">-2.6.35.7</span></li><li>endif</li><li><span style="display:none;">&nbsp;</span></li><li>obj<span class="sh_symbol">-</span>m <span class="sh_symbol">:=</span> $<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>o</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">default</span><span class="sh_symbol">:</span> test driver</li><li><span style="display:none;">&nbsp;</span></li><li>test<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>CC<span class="sh_symbol">)</span> $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>c <span class="sh_symbol">-</span>o $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>driver<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>MAKE<span class="sh_symbol">)</span> <span class="sh_symbol">-</span>C $<span class="sh_symbol">(</span>KERNELDIR<span class="sh_symbol">)</span> M<span class="sh_symbol">=</span>$<span class="sh_symbol">(</span>PWD<span class="sh_symbol">)</span> modules</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>clean<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>f $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>rf <span class="sh_symbol">*.</span>o <span class="sh_symbol">*.</span>ko <span class="sh_symbol">*.</span>mod<span class="sh_symbol">.*</span> <span class="sh_symbol">.</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).*</span> <span class="sh_symbol">.</span>tmp<span class="sh_symbol">*</span> module<span class="sh_symbol">*</span> Module<span class="sh_symbol">*</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;"># makefile for kernel module

MODNAME = chardevicedriver
CROSS_COMPILE = arm-linux-
TESTPRE	= test

ifeq ($(PLATFORM), PC)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
else
CC = $(CROSS_COMPILE)gcc
KERNELDIR ?= /home/tarena/workdir/tools/linux-2.6.35.7
endif

obj-m := $(MODNAME).o

default: test driver

test:
	@echo "Compiling test program..."
	$(CC) $(TESTPRE)$(MODNAME).c -o $(TESTPRE)$(MODNAME)
	@echo

driver:
	@echo "Compiling device driver..."
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@echo

clean:
	@echo "Cleanup test program..."
	@rm -f $(TESTPRE)$(MODNAME)
	@echo
	@echo "Cleanup device driver..."
	@rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
	@echo
</pre></div></div>
    <p class="number">4.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver文件拷贝到指定目录下，执行如下命令。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span><span class="sh_usertype">ko</span><span class="sh_normal">  </span>testchardevicedriver   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko  testchardevicedriver   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">5.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动，如图-5所示。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  insmod   chardevicedriver.ko
</pre></div></div>
    <div class="image">
      <img src="image005.png">
      <p>图-5</p>
    </div>
    <p class="number">6.根据动态分配的主次设备号，手动创建设备文件节点，如图-6所示。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#   mknod  <span class="sh_symbol">/</span>dev<span class="sh_symbol">/</span>chardevicedriver   c    <span class="sh_number">251</span>   <span class="sh_number">0</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#   mknod  /dev/chardevicedriver   c    251   0
</pre></div></div>
    <div class="image">
      <img src="image006.png">
      <p>图-6</p>
    </div>
    <p class="number">7.运行应用测试程序，测试驱动程序，如图-7所示。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_symbol">./</span> testchardevicedriver</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  ./ testchardevicedriver
</pre></div></div>
    <div class="image">
      <img src="image007.png">
      <p>图-7</p>
    </div>
    <h3>2.4 扩展</h3>
    <a name="case3">
    </a>
    <h2>3 按键驱动 V 1.3</h2>
    <h3>3.1 问题</h3>
    <p>为按键驱动实现read和write操作。</p>
    <h3>3.2 方案</h3>
    <p class="number">一、file_operations结构体。</p>
    <p>结构体file_operations在头文件 linux/fs.h中定义，用来存储驱动内核模块提供的对设备进行各种操作的函数的指针。该结构体的每个域都对应着驱动内核模块用来处理某个被请求的事务的函数的地址。</p>
    <p>struct file_operations {</p>
    <p>struct module *owner;</p>
    <p>loff_t(*llseek) (struct file *, loff_t, int);</p>
    <p>ssize_t(*read) (struct file *, char __user *, size_t, loff_t *);</p>
    <p>ssize_t(*aio_read) (struct kiocb *, char __user *, size_t, loff_t);</p>
    <p>ssize_t(*write) (struct file *, const char __user *, size_t, loff_t *);</p>
    <p>ssize_t(*aio_write) (struct kiocb *, const char __user *, size_t, loff_t);</p>
    <p>int (*readdir) (struct file *, void *, filldir_t);</p>
    <p>unsigned int (*poll) (struct file *, struct poll_table_struct *);</p>
    <p>int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long);</p>
    <p>int (*mmap) (struct file *, struct vm_area_struct *);</p>
    <p>int (*open) (struct inode *, struct file *);</p>
    <p>int (*flush) (struct file *);</p>
    <p>int (*release) (struct inode *, struct file *);</p>
    <p>int (*fsync) (struct file *, struct dentry *, int datasync);</p>
    <p>int (*aio_fsync) (struct kiocb *, int datasync);</p>
    <p>int (*fasync) (int, struct file *, int);</p>
    <p>int (*lock) (struct file *, int, struct file_lock *);</p>
    <p>ssize_t(*readv) (struct file *, const struct iovec *, unsigned long, loff_t *);</p>
    <p>ssize_t(*writev) (struct file *, const struct iovec *, unsigned long, loff_t *);</p>
    <p>ssize_t(*sendfile) (struct file *, loff_t *, size_t, read_actor_t, void __user *);</p>
    <p>ssize_t(*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);</p>
    <p>unsigned long (*get_unmapped_area) (struct file *, unsigned long,</p>
    <p>unsigned long, unsigned long,</p>
    <p>unsigned long);</p>
    <p>};</p>
    <p>驱动内核模块并不需要实现每个函数，那么，相对应的file_operations中的项就置为 NULL。</p>
    <p>使用这种结构体的方式如下：</p>
    <p>struct file_operations fops = {</p>
    <p>read: device_read,</p>
    <p>write: device_write,</p>
    <p>open: device_open,</p>
    <p>release: device_release</p>
    <p>};</p>
    <p class="number">二、实现read和write两个函数。</p>
    <p class="number">1.设备读操作。</p>
    <p>读操作就是从设备中读取数据到用户空间，如图-8所示。如果该操作为空，将使得read系统调用返回负EINVAL失败，正常返回实际读取的字节数</p>
    <p>ssize_t (*read)(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);</p>
    <p>filp: 待操作的设备文件file结构体指针</p>
    <p>buf: 待写入所读取数据的用户空间缓冲区指针</p>
    <p>count: 待读取数据字节数</p>
    <p>f_pos: 待读取数据文件位置，读取完成后根据实际读取字节数重新定位</p>
    <p>返回: 成功实际读取的字节数，失败返回负值</p>
    <p>(*read)(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);</p>
    <div class="image">
      <img src="image008.png">
      <p>图-8</p>
    </div>
    <p class="number">2.设备写操作。</p>
    <p>写操作就是将数据从用户空间写入到设备，如图-9所示。如果该操作为空，将使得write系统调用返回负EINVAL失败，正常返回实际写入的字节数</p>
    <p>ssize_t (*write)(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);</p>
    <p>filp: 待操作的设备文件file结构体指针</p>
    <p>buf: 待写入所读取数据的用户空间缓冲区指针</p>
    <p>count: 待读取数据字节数</p>
    <p>f_pos: 待读取数据文件位置，写入完成后根据实际写入字节数重新定位</p>
    <p>返回: 成功实际写入的字节数，失败返回负值</p>
    <p>(*write)(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);</p>
    <div class="image">
      <img src="image009.png">
      <p>图-9</p>
    </div>
    <p>读和写方法的buf都是用户空间指针，它不能在内核模块中直接使用。为此，内核为驱动程序提供在内核空间和用户空间传递数据的方法。</p>
    <p>定义在arch/arm/include/asm/uaccess.h中 。</p>
    <p>（1）用户空间-&gt;内核空间</p>
    <p>（2）内核空间-&gt;用户空间</p>
    <p>（3）用户空间内存可访问性验证</p>
    <p>（4）数据传送函数会检查用户空间内核是否可访问</p>
    <p class="number">三、数据从用户空间到内核空间。</p>
    <p class="number">1.copy_from_user函数。</p>
    <p>unsigned long copy_from_user(void *to, const void *from, unsigned long n);</p>
    <p>to: 目标地址(内核空间)</p>
    <p>from: 源地址(用户空间)</p>
    <p>n: 将要拷贝数据的字节数</p>
    <p>返回: 成功返回0，失败返回没有拷贝成功的数据字节数</p>
    <p class="number">2.get_user宏</p>
    <p>int get_user(data, ptr);</p>
    <p>data: 可以是字节、半字、字、双字类型的内核变量</p>
    <p>ptr: 用户空间内存指针</p>
    <p>返回: 成功返回0，失败返回非0</p>
    <p class="number">四、数据从内核空间到用户空间。</p>
    <p class="number">1.copy_to_user函数。</p>
    <p>unsigned long copy_to_user(void *to, const void *from, unsigned long n);</p>
    <p>to: 目标地址(用户空间)</p>
    <p>from: 源地址(内核空间)</p>
    <p>n: 将要拷贝数据的字节数</p>
    <p>返回: 成功返回0，失败返回没有拷贝成功的数据字节数</p>
    <p class="number">2.put_user宏。</p>
    <p>int put_user(data, ptr);</p>
    <p>data: 可以是字节、半字、字、双字类型的内核变量</p>
    <p>ptr: 用户空间内存指针</p>
    <p>返回: 成功返回0，失败返回非0</p>
    <p class="number">五、用户空间内存可访问性验证。</p>
    <p class="number">1.access_ok宏 。</p>
    <p>int access_ok(int type, const void *addr, unsigned long size);</p>
    <p>type: 取值为VERIFY_READ或VERIFY_WRITE，表示是读用户内存还是写用户内存</p>
    <p>addr: 待验证的用户内存地址</p>
    <p>size: 待验证的用户内存长度</p>
    <p>返回值: 返回非0代表用户内存可访问，返回0代表失败(存取有问题)，如果失败，ioctl操作应该返回-EFAULT</p>
    <p class="number">六、本案例的操作步骤如下。</p>
    <p class="number">1.编写chardevicedriver.c源文件。</p>
    <p>（1） 在chardevicedriver_init（）函数中，使用gpio_request（）函数为TPAD上的KEY1UP键申请GPIO端口，名为Button；</p>
    <p>（2）实现函数chardevicedriver_read（），使用gpio_get_value（）函数获取该引脚的高低电平，并使用copy_to_user（）函数将该值复制给用户空间的buf变量；</p>
    <p>（3）实现函数chardevicedriver_write（），使用copy_from_user（）函数将用户空间的buf变量里的值赋值给内核空间的变量xbuf，并将变量xbuf中的值在内核空间打印输出；</p>
    <p>（4）将实现了的chardevicedriver_read（），chardevicedriver_write（）两个函数赋值给结构体chardevicedriver_fops中的read和write两接口；</p>
    <p>（5）在chardevicedriver_exit（）函数中，使用gpio_free（）函数为释放KEY1UP按键的GPIO端口使用权；</p>
    <p class="number">2.编写testchardevicedriver.c源文件。</p>
    <p class="number">3.编写Makefile文件。</p>
    <p class="number">4.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko拷贝到指定目录 。</p>
    <p class="number">5.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p class="number">6.根据动态分配的主次设备号，手动创建设备文件节点。</p>
    <p class="number">7.运行应用测试程序，测试驱动程序。</p>
    <h3>3.3 实现</h3>
    <p class="number">1.编写chardevicedriver.c源文件，实现read、write函数。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span class="sh_comment">// licensed under BSD/GPL</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">1</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_major <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_minor <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> struct <span class="sh_usertype">cdev</span><span class="sh_normal"> </span>chardevicedriver_cdev<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_open</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardeivcedriver_open !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_read</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;unsigned <span class="sh_type">char</span> key_value<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">size_t</span><span class="sh_normal">  </span>cnt <span class="sh_symbol">=</span> count<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;key_value <span class="sh_symbol">=</span> <span class="sh_function">gpio_get_value</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">copy_to_user</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>key_value<span class="sh_symbol">,</span> cnt<span class="sh_symbol">))</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> count<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_write</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_keyword">const</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>       <span class="sh_usertype">size_t</span><span class="sh_normal">  </span>cnt <span class="sh_symbol">=</span> count<span class="sh_symbol">;</span></li><li>       <span class="sh_type">char</span> xbuf<span class="sh_symbol">[</span><span class="sh_number">10</span><span class="sh_symbol">];</span></li><li>       <span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_write !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>       </li><li>       <span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">copy_from_user</span><span class="sh_symbol">(</span>xbuf<span class="sh_symbol">,</span>buf<span class="sh_symbol">,</span> cnt<span class="sh_symbol">))</span> <span class="sh_cbracket">{</span> </li><li>                <span class="sh_keyword">return</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>       <span class="sh_cbracket">}</span></li><li>       <span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"xbuf[10]=%s</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span>xbuf<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_release</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_release !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file_operations</span><span class="sh_normal"> </span>chardevicedriver_fops <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>owner&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> THIS_MODULE<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>open&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_open<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>read&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_read<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>write&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_write<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>release<span class="sh_symbol">=</span> chardevicedriver_release<span class="sh_symbol">,</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> chardevicedriver_major <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// static device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">register_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">else</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// dynamic device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">alloc_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>dev<span class="sh_symbol">,</span> chardevicedriver_minor<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_major <span class="sh_symbol">=</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">memset</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev<span class="sh_symbol">,</span> <span class="sh_number">0</span><span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>cdev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_init</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>chardevicedriver_fops <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">cdev_add</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev<span class="sh_symbol">,</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Failure to add cdev to kernel, return value = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> ret<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_add_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li> ret <span class="sh_symbol">=</span> <span class="sh_function">gpio_request</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">),</span> <span class="sh_string">"Button"</span><span class="sh_symbol">);</span>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span>ret<span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"gpio_request failed.</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_add_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to add cdev to kernel !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_add_cdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// delete cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_del</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>chardevicedriver_cdev <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li><span class="sh_function">gpio_free</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Exit chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;linux/uaccess.h&gt;
#include &lt;linux/gpio.h&gt;
// licensed under BSD/GPL
MODULE_LICENSE("Dual BSD/GPL");

#define CHARDEVICEDRIVER_MAJOR		0
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		1
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"

static u32 chardevicedriver_major = CHARDEVICEDRIVER_MAJOR;
static u32 chardevicedriver_minor = CHARDEVICEDRIVER_MINOR;

static struct cdev chardevicedriver_cdev;

static int chardevicedriver_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardeivcedriver_open !\n");

	return 0;
}

static ssize_t chardevicedriver_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	unsigned char key_value;
	size_t  cnt = count;
	key_value = gpio_get_value(S5PV210_GPH0(0));
	if(copy_to_user(buf, &amp;key_value, cnt)) {
		return -EFAULT;
	}
	return count;
}

static ssize_t chardevicedriver_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
       size_t  cnt = count;
       char xbuf[10];
       printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_write !\n");
       
       if(copy_from_user(xbuf,buf, cnt)) { 
                return -EFAULT;
       }
       printk(KERN_ALERT "xbuf[10]=%s\n",xbuf);
	return 0;
}

static int chardevicedriver_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_release !\n");

	return 0;
}

static struct file_operations chardevicedriver_fops = {
	.owner	= THIS_MODULE,
	.open	= chardevicedriver_open,
	.read	= chardevicedriver_read,
	.write	= chardevicedriver_write,
	.release= chardevicedriver_release,
};

// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

	// register device number
	if( chardevicedriver_major ) { // static device number
		dev = MKDEV( chardevicedriver_major, chardevicedriver_minor );
		ret = register_chrdev_region( dev, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	}
	else { // dynamic device number
		ret = alloc_chrdev_region( &amp;dev, chardevicedriver_minor, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
		chardevicedriver_major = MAJOR( dev );
	}
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", chardevicedriver_major);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: Device Major = %d !\n", chardevicedriver_major);

	// register cdev object
	memset( &amp;chardevicedriver_cdev, 0, sizeof( struct cdev ) );
	cdev_init( &amp;chardevicedriver_cdev, &amp;chardevicedriver_fops );
	ret = cdev_add( &amp;chardevicedriver_cdev, dev, CHARDEVICEDRIVER_COUNT );
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Failure to add cdev to kernel, return value = %d !\n", ret);
		goto failure_add_cdev;
	}
 ret = gpio_request(S5PV210_GPH0(0), "Button");	
	if(ret) {
		printk(KERN_ALERT "gpio_request failed.\n");
		goto failure_add_cdev;
	}	
	printk(KERN_ALERT "CharDeviceDriver: Success to add cdev to kernel !\n");

	return ret;

failure_add_cdev:
	unregister_chrdev_region( dev, CHARDEVICEDRIVER_COUNT );
failure_register_chrdev:
	return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");

	// delete cdev object
	cdev_del( &amp;chardevicedriver_cdev );

	// unregister device number
	unregister_chrdev_region( MKDEV( chardevicedriver_major, chardevicedriver_minor ), CHARDEVICEDRIVER_COUNT );
gpio_free(S5PV210_GPH0(0));
	printk(KERN_ALERT "CharDeviceDriver: Exit chardevicedriver_exit !\n");
}

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">2.编写testchardevicedriver.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>stdio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>stdlib<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>fcntl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> fd<span class="sh_symbol">;</span></li><li><span class="sh_type">char</span> buf<span class="sh_symbol">[</span> <span class="sh_number">10</span> <span class="sh_symbol">]=</span><span class="sh_string">"Hello,Key!"</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">(</span><span class="sh_type">int</span> argc<span class="sh_symbol">,</span> <span class="sh_type">char</span> <span class="sh_symbol">**</span>argv<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;unsigned <span class="sh_type">char</span> key_value <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>        &nbsp;&nbsp;&nbsp;&nbsp;</li><li> fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Failure to open device file: /dev/chardevicedriver!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">exit</span><span class="sh_symbol">(</span> <span class="sh_symbol">-</span><span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to open device file: /dev/chardevicedriver!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">while</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">read</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>key_value<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>key_value<span class="sh_symbol">));</span> </li><li>      <span class="sh_keyword">if</span> <span class="sh_symbol">(</span>ret <span class="sh_symbol">==</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"read button failed.</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>          <span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>      <span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"key value = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> key_value<span class="sh_symbol">);</span></li><li>      <span class="sh_function">write</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> buf<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">close</span><span class="sh_symbol">(</span> fd <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to test device: /dev/chardevicedriver !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;

int fd;
char buf[ 10 ]="Hello,Key!";

int main(int argc, char **argv)
{
	unsigned char key_value = 0;
int ret = 0;
        	
 fd = open( "/dev/chardevicedriver", O_RDWR );
	if( 0 &gt; fd ) {
		printf("Failure to open device file: /dev/chardevicedriver!\n");
		exit( -1 );
	}
	printf("Success to open device file: /dev/chardevicedriver!\n");

	while( 1 ) {
		ret = read(fd, &amp;key_value, sizeof(key_value)); 
      if (ret == -1) {
			printf("read button failed.\n");
          return -1;
		}
      printf("key value = %d\n", key_value);
      write(fd, buf, sizeof(buf));
	}

	close( fd );
	printf("Success to test device: /dev/chardevicedriver !\n");

	return 0;
}
</pre></div></div>
    <p class="number">3.编写Makefile文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li># makefile <span class="sh_keyword">for</span> kernel module</li><li><span style="display:none;">&nbsp;</span></li><li>MODNAME <span class="sh_symbol">=</span> chardevicedriver</li><li>CROSS_COMPILE <span class="sh_symbol">=</span> arm<span class="sh_symbol">-</span>linux<span class="sh_symbol">-</span></li><li>TESTPRE&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> test</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">ifeq</span> <span class="sh_symbol">(</span>$<span class="sh_symbol">(</span>PLATFORM<span class="sh_symbol">),</span> PC<span class="sh_symbol">)</span></li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>lib<span class="sh_symbol">/</span>modules<span class="sh_symbol">/</span>$<span class="sh_symbol">(</span><span class="sh_usertype">shell</span><span class="sh_normal"> </span>uname <span class="sh_symbol">-</span>r<span class="sh_symbol">)/</span>build</li><li><span class="sh_keyword">else</span></li><li>CC <span class="sh_symbol">=</span> $<span class="sh_symbol">(</span>CROSS_COMPILE<span class="sh_symbol">)</span>gcc</li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>tools<span class="sh_symbol">/</span>linux<span class="sh_number">-2.6.35.7</span></li><li>endif</li><li><span style="display:none;">&nbsp;</span></li><li>obj<span class="sh_symbol">-</span>m <span class="sh_symbol">:=</span> $<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>o</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">default</span><span class="sh_symbol">:</span> test driver</li><li><span style="display:none;">&nbsp;</span></li><li>test<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>CC<span class="sh_symbol">)</span> $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>c <span class="sh_symbol">-</span>o $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>driver<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>MAKE<span class="sh_symbol">)</span> <span class="sh_symbol">-</span>C $<span class="sh_symbol">(</span>KERNELDIR<span class="sh_symbol">)</span> M<span class="sh_symbol">=</span>$<span class="sh_symbol">(</span>PWD<span class="sh_symbol">)</span> modules</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>clean<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>f $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>rf <span class="sh_symbol">*.</span>o <span class="sh_symbol">*.</span>ko <span class="sh_symbol">*.</span>mod<span class="sh_symbol">.*</span> <span class="sh_symbol">.</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).*</span> <span class="sh_symbol">.</span>tmp<span class="sh_symbol">*</span> module<span class="sh_symbol">*</span> Module<span class="sh_symbol">*</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;"># makefile for kernel module

MODNAME = chardevicedriver
CROSS_COMPILE = arm-linux-
TESTPRE	= test

ifeq ($(PLATFORM), PC)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
else
CC = $(CROSS_COMPILE)gcc
KERNELDIR ?= /home/tarena/workdir/tools/linux-2.6.35.7
endif

obj-m := $(MODNAME).o

default: test driver

test:
	@echo "Compiling test program..."
	$(CC) $(TESTPRE)$(MODNAME).c -o $(TESTPRE)$(MODNAME)
	@echo

driver:
	@echo "Compiling device driver..."
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@echo

clean:
	@echo "Cleanup test program..."
	@rm -f $(TESTPRE)$(MODNAME)
	@echo
	@echo "Cleanup device driver..."
	@rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
	@echo
</pre></div></div>
    <p class="number">4.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver文件拷贝到指定目录下，执行如下命令。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span><span class="sh_usertype">ko</span><span class="sh_normal">  </span>testchardevicedriver   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko  testchardevicedriver   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">5.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  insmod   chardevicedriver.ko
</pre></div></div>
    <p class="number">6.根据动态分配的主次设备号，手动创建设备文件节点。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#   mknod  <span class="sh_symbol">/</span>dev<span class="sh_symbol">/</span>chardevicedriver   c    <span class="sh_number">251</span>   <span class="sh_number">0</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#   mknod  /dev/chardevicedriver   c    251   0
</pre></div></div>
    <p class="number">7.运行应用测试程序，测试驱动程序。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_symbol">./</span> testchardevicedriver</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  ./ testchardevicedriver
</pre></div></div>
    <p>测试程序运行过程中，在未按下TPAD上的按键时，读出来key  value 的值为1，当按下TPAD上的KEY1UP键时，读出来的key value值为0，如图-10所示。由用户测试程序向设备中写的“Hello  Key!”字符串，在内核空间中输出了，如图-11所示。</p>
    <div class="image">
      <img src="image010.png">
      <p>图-10</p>
    </div>
    <div class="image">
      <img src="image011.png">
      <p>图-11</p>
    </div>
    <h3>3.4 扩展</h3>
    <a name="case4">
    </a>
    <h2>4 按键驱动 V 1.4</h2>
    <h3>4.1 问题</h3>
    <p>为按键驱动实现ioctl操作。</p>
    <h3>4.2 方案</h3>
    <p class="number">一、ioctl（）函数。</p>
    <p>在驱动程序里， ioctl() 函数是用来控制I/O设备 ，提供了一种获得设备信息和向设备发送控制参数的手段。用于向设备发控制和配置命令 ，有些命令需要控制参数，这些数据是不能用read / write 读写的，称为Out-of-band数据。也就是说，read / write 读写的数据是in-band数据,是I/O操作的主体，而ioctl 命令传送的是控制信息,其中的数据是辅助的数据。</p>
    <p>ioctl() 函数传送的变量 cmd 是应用程序用于区别设备驱动程序请求处理内容的值。cmd除了可区别数字外，还包含有助于处理的几种相应信息。</p>
    <p>在驱动程式中实现的ioctl函数体内，实际上是有一个switch{case}结构，每一个case对应一个命令码，做出一些相应的操作。怎么实现这些操作，这是每一个程式员自己的事情，因为设备都是特定的，这里也没法说。关键在于怎么样组织命令码，因为在ioctl中命令码是唯一联系用户程式命令和驱动程式支持的途径。</p>
    <p>命令码的组织是有一些讲究的，因为我们一定要做到命令和设备是一一对应的，这样才不会将正确的命令发给错误的设备，或是把错误的命令发给正确的设备，或是把错误的命令发给错误的设备。这些错误都会导致不可预料的事情发生，而当程式员发现了这些奇怪的事情的时候，再来调试程式查找错误，那将是非常困难的事情。</p>
    <p>所以在Linux核心中是这样定义一个命令码的：</p>
    <p>____________________________________</p>
    <p>| 设备类型 | 序列号 | 方向 |数据尺寸|</p>
    <p>|----------|--------|------|--------|</p>
    <p>|   8 bit   | 8 bit  |2 bit |8~14 bit|</p>
    <p>|----------|--------|------|--------|</p>
    <p>这样一来，一个命令就变成了一个整数形式的命令码。不过命令码非常的不直观，所以Linux Kernel中提供了一些宏，这些宏可根据便于理解的字符串生成命令码，或是从命令码得到一些用户能理解的字符串以标明这个命令对应的设备类型、设备序列号、数据传送方向和数据传输尺寸。</p>
    <p>这些宏我就不在这里解释了，具体的形式请读者察看Linux核心原始码中的和，文件里给除了这些宏完整的定义。这里我只多说一个地方，那就是"幻数"。</p>
    <p class="number">1.幻数。</p>
    <p>幻数是个字母，数据长度也是8，所以就用一个特定的字母来标明设备类型，这和用一个数字是相同的，只是更加利于记忆和理解。就是这样，再没有更复杂的了。</p>
    <p>以上几个宏的使用格式为：</p>
    <p>_IO (魔数， 基数)；</p>
    <p>_IOR (魔数， 基数， 变量型)；</p>
    <p>_IOW &nbsp;(魔数， 基数， 变量型)；</p>
    <p>_IOWR (魔数， 基数，变量型 )；</p>
    <p class="number">2.魔数 (magic number)。</p>
    <p>魔数范围为 0~255 。通常，用英文字符 "A" ~ "Z" 或者 "a" ~ "z" 来表示。设备驱动程序从传递进来的命令获取魔数，然后与自身处理的魔数想比较，如果相同则处理，不同则不处理。魔数是拒绝误使用的初步辅助状态。设备驱动程序可以通过 _IOC_TYPE (cmd)来获取魔数。不同的设备驱动程序最好设置不同的魔数，但并不是要求绝对，也是可以使用其他设备驱动程序已用过的魔数。</p>
    <p class="number">3.基(序列号)数。</p>
    <p>基数用于区别各种命令。通常，从 0开始递增，相同设备驱动程序上可以重复使用该值。例如，读取和写入命令中使用了相同的基数，设备驱动程序也能分辨出来，原因在于设备驱动程序区分命令时使用 switch ，且直接使用命令变量 cmd值。创建命令的宏生成的值由多个域组合而成，所以即使是相同的基数，也会判断为不同的命令。设备驱动程序想要从命令中获取该基数，就使用下面的宏：</p>
    <p>_IOC_NR (cmd)</p>
    <p>通常，switch中的case值使用的是命令的本身。</p>
    <p class="number">4.变量型。</p>
    <p>变量型使用 arg 变量指定传送的数据大小，但是不直接代入输入，而是代入变量或者是变量的类型，原因是在使用宏创建命令，已经包含了 sizeof() 编译命令。</p>
    <p class="number">二、本案例的操作步骤如下。</p>
    <p class="number">1. 编写chardevicedriverioctlled.h头文件。</p>
    <p>（1）定义基数宏LED_IOCOMMAND_ON、LED_IOCOMMAND_OFF分别为0x80,0x81；</p>
    <p>（2）定义幻数宏LED_IOCTL_MAGIC为1；</p>
    <p>（3）定义cmd命令宏，由_IO宏通过幻数和基数来生成cmd；</p>
    <p>1）#define LED_IOCTL_ON	    _IO( LED_IOCTL_MAGIC, LED_IOCOMMAND_ON )</p>
    <p>2）#define LED_IOCTL_OFF    _IO( LED_IOCTL_MAGIC, LED_IOCOMMAND_OFF )</p>
    <p class="number">2.编写chardevicedriver.c源文件。</p>
    <p>（1） 定义描述设备的结构体chardevicedriver_cdev，成员变量包括cdev和u8 led，并定义该类型的全局变量*chardevicedriver_cdevp，并赋值为NULL；</p>
    <p>（2）定义描述TPAD上的led灯使用的GPIO管脚号的数组long led_gpio_table[ CHARDEVICEDRIVER_COUNT ]；</p>
    <p>（3）在chardevicedriver_init（）函数中，使用kmalloc（）函数为设备结构体变量*chardevicedriver_cdevp分配内核空间，再用memset（）函数为其初始化为0，在使用cdev_init（）和cdev_add（）分别初始化该变量和添加到内核；</p>
    <p>（4）在函数chardevicedriver_open（）中，</p>
    <p>1）定义chardevicedriver_cdev类型的局部指针变量*pcdevp；</p>
    <p>2）使用container_of（）函数获取全局变量chardevicedriver_cdevp的地址，并复制给局部变量pcdevp；</p>
    <p>3）接下来为led1申请所使用到的GPIO管脚号S5PV210_GPC1(3)；</p>
    <p>4）最后调用chardevicedriver_led_control（）函数为led1灯进行初始化；</p>
    <p>（5）实现函数chardevicedriver_led_control（），功能是对GPIO管脚的操作，使用gpio_direction_output( )函数将相对应参数的GPIO管脚设置为输出端口，使用s3c_gpio_setpull（）函数禁止该管脚的内部上下拉电阻，使用	gpio_set_value（）为该管脚写值，0或1，已达到控制led灯的亮灭；</p>
    <p>（6）实现函数chardevicedriver_ioctl（），实现控制led灯亮灭的功能；</p>
    <p>1）使用宏_IOC_TYPE (cmd)来获取魔数；</p>
    <p>2）使用宏_IOC_NR (cmd)来获取基数；</p>
    <p>3）使用宏_IOC_DIR(cmd)取命令cmd的方向字段；</p>
    <p>4）将它们分别与在chardevicedriverioctlled.h头文件中定义的相对应的宏进行验证；</p>
    <p>5）当所有项都匹配成功之后，使用switch-case语句来对cmd命令进行匹配，并根据匹配的不同结果给一个控制led灯亮灭的变量pcdevp-&gt;led赋不同的值；</p>
    <p>6）调用chardevicedriver_led_control（）函数实现对led1灯的亮灭控制；</p>
    <p>（7）将实现了的chardevicedriver_ioctl（）函数赋值给结构体chardevicedriver_fops中的ioctl接口；</p>
    <p>（8）在chardevicedriver_release（）函数中，使用gpio_free（）函数为释放KEY1UP按键的GPIO端口使用权；</p>
    <p>（9）在chardevicedriver_exit（）函数中使用kfree（）函数释放*chardevicedriver_cdevp所占用的内存空间；</p>
    <p class="number">3.编写testchardevicedriver.c源文件。</p>
    <p class="number">4.编写Makefile文件。</p>
    <p class="number">5.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko拷贝到指定目录。</p>
    <p class="number">6.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p class="number">7.根据动态分配的主次设备号，手动创建设备文件节点。</p>
    <p class="number">8.运行应用测试程序，测试驱动程序。</p>
    <h3>4.3 实现</h3>
    <p class="number">1.编写chardevicedriverioctlled.h头文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriverioctlled<span class="sh_symbol">.</span>h</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriverioctlled.h
</pre></div></div>
    <p>chardevicedriverioctlled.h源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_comment">// the definition of IOCTL for led</span></li><li><span style="display:none;">&nbsp;</span></li><li>#ifndef __CHARDEVICEDRIVERIOCTLLED_H__</li><li>#define __CHARDEVICEDRIVERIOCTLLED_H__</li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>LED_IOCOMMAND_ON&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0x80</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>LED_IOCOMMAND_OFF&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0x81</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>LED_IOCTL_MAGIC&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">'l'</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span><span class="sh_usertype">LED_IOCTL_NR_MIN</span><span class="sh_normal">&nbsp;&nbsp;&nbsp;&nbsp;</span>LED_IOCOMMAND_ON</li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span><span class="sh_usertype">LED_IOCTL_NR_MAX</span><span class="sh_normal">&nbsp;&nbsp;&nbsp;&nbsp;</span>LED_IOCOMMAND_OFF</li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>LED_IOCTL_ON&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">_IO</span><span class="sh_symbol">(</span> LED_IOCTL_MAGIC<span class="sh_symbol">,</span> LED_IOCOMMAND_ON <span class="sh_symbol">)</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>LED_IOCTL_OFF&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">_IO</span><span class="sh_symbol">(</span> LED_IOCTL_MAGIC<span class="sh_symbol">,</span> LED_IOCOMMAND_OFF <span class="sh_symbol">)</span></li><li>#endif</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">// the definition of IOCTL for led

#ifndef __CHARDEVICEDRIVERIOCTLLED_H__
#define __CHARDEVICEDRIVERIOCTLLED_H__
#define LED_IOCOMMAND_ON	0x80
#define LED_IOCOMMAND_OFF	0x81

#define LED_IOCTL_MAGIC		'l'

#define LED_IOCTL_NR_MIN	LED_IOCOMMAND_ON
#define LED_IOCTL_NR_MAX	LED_IOCOMMAND_OFF

#define LED_IOCTL_ON		_IO( LED_IOCTL_MAGIC, LED_IOCOMMAND_ON )
#define LED_IOCTL_OFF		_IO( LED_IOCTL_MAGIC, LED_IOCOMMAND_OFF )
#endif
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">2.编写chardevicedriver.c源文件，实现ioctl函数。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_comment">// include kernel head files</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>device<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>plat<span class="sh_symbol">/</span>gpio<span class="sh_symbol">-</span>cfg<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>slab<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_string">"chardevicedriverioctlled.h"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// licensed under BSD/GPL</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">1</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_major <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_minor <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;struct <span class="sh_usertype">cdev</span><span class="sh_normal"> </span>cdev<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">u8</span><span class="sh_normal"> </span>led<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>chardevicedriver_cdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> unsigned <span class="sh_type">long</span> led_gpio_table<span class="sh_symbol">[</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">]</span> <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>    <span class="sh_function">S5PV210_GPC1</span><span class="sh_symbol">(</span><span class="sh_number">3</span><span class="sh_symbol">),</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> <span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span><span class="sh_type">int</span> index<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">gpio_direction_output</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">s3c_gpio_setpull</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> S3C_GPIO_PULL_NONE <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">gpio_set_value</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_open</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// struct inode:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//  &nbsp;&nbsp;&nbsp;&nbsp;dev_t i_rdev: device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//&nbsp;&nbsp;&nbsp;&nbsp;struct cdev *i_cdev: private cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// struc file:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//&nbsp;&nbsp;&nbsp;&nbsp;void *private_data;</span></li><li> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> index<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardeivcedriver_open !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;pcdevp <span class="sh_symbol">=</span> <span class="sh_function">container_of</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_cdev<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev<span class="sh_symbol">,</span> cdev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;filp<span class="sh_symbol">-&gt;</span>private_data <span class="sh_symbol">=</span> pcdevp<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;index <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_rdev <span class="sh_symbol">)</span> <span class="sh_symbol">-</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">gpio_request</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">0</span><span class="sh_symbol">],</span> <span class="sh_string">"GPC1_3"</span><span class="sh_symbol">))</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"gpio_request failed!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span> index<span class="sh_symbol">,</span> pcdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_read</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_read !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_write</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_keyword">const</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_write !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_ioctl</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> unsigned <span class="sh_type">int</span> cmd<span class="sh_symbol">,</span> unsigned <span class="sh_type">long</span> arg<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> index <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_rdev <span class="sh_symbol">)</span> <span class="sh_symbol">-</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_ioctl !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// check device type</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> LED_IOCTL_MAGIC <span class="sh_symbol">!=</span> <span class="sh_function">_IOC_TYPE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: ioctype mismatch !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// check ioctl nr</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_symbol">(</span> LED_IOCTL_NR_MIN <span class="sh_symbol">&gt;</span> <span class="sh_function">_IOC_NR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">||</span> <span class="sh_symbol">(</span> LED_IOCTL_NR_MAX <span class="sh_symbol">&lt;</span> <span class="sh_function">_IOC_NR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: iocnr mismatch !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// check access_ok for user space memory</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> _IOC_READ <span class="sh_symbol">&amp;</span> <span class="sh_function">_IOC_DIR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_symbol">!</span><span class="sh_function">access_ok</span><span class="sh_symbol">(</span> VERIFY_WRITE<span class="sh_symbol">,</span> arg<span class="sh_symbol">,</span> <span class="sh_function">_IOC_SIZE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: cann't access to write user space memory !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> _IOC_WRITE <span class="sh_symbol">&amp;</span> <span class="sh_function">_IOC_DIR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_symbol">!</span><span class="sh_function">access_ok</span><span class="sh_symbol">(</span> VERIFY_READ<span class="sh_symbol">,</span> arg<span class="sh_symbol">,</span> <span class="sh_function">_IOC_SIZE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: cann't access to read user space memory !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// print all fields of cmd</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: cmd = 0x%8x, ioctype = 0x%8x, iocnr = 0x%8x, iocdir = 0x%8x, iocsize = 0x%8x !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> cmd<span class="sh_symbol">,</span> <span class="sh_function">_IOC_TYPE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">),</span> <span class="sh_function">_IOC_NR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">),</span> <span class="sh_function">_IOC_DIR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">),</span> <span class="sh_function">_IOC_SIZE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">));</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// handle ioctl command</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">switch</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> LED_IOCTL_ON<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">=</span> <span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> LED_IOCTL_OFF<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">default</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: unknown ioctl command !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span> index<span class="sh_symbol">,</span> pcdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_release</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_release !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span class="sh_function">gpio_free</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">0</span><span class="sh_symbol">]);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file_operations</span><span class="sh_normal"> </span>chardevicedriver_fops <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>owner&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> THIS_MODULE<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>open&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_open<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>read&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_read<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>write&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_write<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>ioctl&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_ioctl<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>release<span class="sh_symbol">=</span> chardevicedriver_release<span class="sh_symbol">,</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> chardevicedriver_major <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// static device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">register_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">else</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// dynamic device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">alloc_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>dev<span class="sh_symbol">,</span> chardevicedriver_minor<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_major <span class="sh_symbol">=</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// allocate memory for private struct including struct cdev</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_cdevp <span class="sh_symbol">=</span> <span class="sh_function">kmalloc</span><span class="sh_symbol">(</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_symbol">)</span> <span class="sh_symbol">*</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> GFP_KERNEL <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: No enough memory for private struct !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_alloc_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">memset</span><span class="sh_symbol">(</span> chardevicedriver_cdevp<span class="sh_symbol">,</span> <span class="sh_number">0</span><span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_symbol">)</span> <span class="sh_symbol">*</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>      <span class="sh_function">cdev_init</span><span class="sh_symbol">(&amp;(</span>chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">),</span> <span class="sh_symbol">&amp;</span>chardevicedriver_fops <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">cdev_add</span><span class="sh_symbol">(&amp;(</span>chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">),</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Failure to add cdev to kernel, return value = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> ret<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_add_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to add cdev to kernel ! Major: %d</span><span class="sh_specialchar">\t</span><span class="sh_string">Minor: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">),</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_add_cdev<span class="sh_symbol">:</span></li><li>       <span class="sh_function">kfree</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>failure_alloc_cdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;      <span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;      <span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// destroy device and delete cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">for</span><span class="sh_symbol">(</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span> i <span class="sh_symbol">&lt;</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">;</span> i<span class="sh_symbol">++</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_del</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span> chardevicedriver_cdevp<span class="sh_symbol">[</span> i <span class="sh_symbol">].</span>cdev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li> &nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// free memory for private struct</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">kfree</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_cdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Exit chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">// include kernel head files
#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;linux/device.h&gt;

#include &lt;asm/uaccess.h&gt;

#include &lt;asm/gpio.h&gt;
#include &lt;plat/gpio-cfg.h&gt;
#include &lt;linux/slab.h&gt;

#include "chardevicedriverioctlled.h"

// licensed under BSD/GPL
MODULE_LICENSE("Dual BSD/GPL");

#define CHARDEVICEDRIVER_MAJOR		0
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		1
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"


static u32 chardevicedriver_major = CHARDEVICEDRIVER_MAJOR;
static u32 chardevicedriver_minor = CHARDEVICEDRIVER_MINOR;
struct chardevicedriver_cdev {
	struct cdev cdev;

	u8 led;
};
static struct chardevicedriver_cdev *chardevicedriver_cdevp = NULL;
static unsigned long led_gpio_table[ CHARDEVICEDRIVER_COUNT ] = {
    S5PV210_GPC1(3),
};
static void chardevicedriver_led_control(int index, struct chardevicedriver_cdev *pcdevp)
{
	gpio_direction_output( led_gpio_table[ index ], 0 );
	s3c_gpio_setpull( led_gpio_table[ index ], S3C_GPIO_PULL_NONE );
	gpio_set_value( led_gpio_table[ index ], pcdevp-&gt;led );
}

static int chardevicedriver_open(struct inode *inode, struct file *filp)
{
	// struct inode:
	//  	dev_t i_rdev: device number
	//	struct cdev *i_cdev: private cdev object
	// struc file:
	//	void *private_data;
 struct chardevicedriver_cdev *pcdevp = NULL;
	int index;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardeivcedriver_open !\n");
	pcdevp = container_of( inode-&gt;i_cdev, struct chardevicedriver_cdev, cdev );
	filp-&gt;private_data = pcdevp;
	index = MINOR( inode-&gt;i_rdev ) - CHARDEVICEDRIVER_MINOR;
	if(gpio_request(led_gpio_table[0], "GPC1_3"))
	{
		printk(KERN_ALERT "gpio_request failed!\n");
		return -1;
	}
	chardevicedriver_led_control( index, pcdevp );
	return 0;
}

static ssize_t chardevicedriver_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_read !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	return 0;
}

static ssize_t chardevicedriver_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_write !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	return 0;
}

static int chardevicedriver_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;
	int ret = -EFAULT;
	int index = MINOR( inode-&gt;i_rdev ) - CHARDEVICEDRIVER_MINOR;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_ioctl !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	// check device type
	if( LED_IOCTL_MAGIC != _IOC_TYPE( cmd ) ) {
		printk(KERN_ALERT "CharDeviceDriver: ioctype mismatch !\n");
		return ret;
	}
	// check ioctl nr
	if( ( LED_IOCTL_NR_MIN &gt; _IOC_NR( cmd ) ) || ( LED_IOCTL_NR_MAX &lt; _IOC_NR( cmd ) ) ) {
		printk(KERN_ALERT "CharDeviceDriver: iocnr mismatch !\n");
		return ret;
	}
	// check access_ok for user space memory
	if( _IOC_READ &amp; _IOC_DIR( cmd ) ) {
		if( !access_ok( VERIFY_WRITE, arg, _IOC_SIZE( cmd ) ) ) {
			printk(KERN_ALERT "CharDeviceDriver: cann't access to write user space memory !\n");
			return ret;
		}
	}
	if( _IOC_WRITE &amp; _IOC_DIR( cmd ) ) {
		if( !access_ok( VERIFY_READ, arg, _IOC_SIZE( cmd ) ) ) {
			printk(KERN_ALERT "CharDeviceDriver: cann't access to read user space memory !\n");
			return ret;
		}
	}
	// print all fields of cmd
	printk(KERN_ALERT "CharDeviceDriver: cmd = 0x%8x, ioctype = 0x%8x, iocnr = 0x%8x, iocdir = 0x%8x, iocsize = 0x%8x !\n", cmd, _IOC_TYPE( cmd ), _IOC_NR( cmd ), _IOC_DIR( cmd ), _IOC_SIZE( cmd ));

	// handle ioctl command
	ret = 0;
	switch( cmd ) {
	case LED_IOCTL_ON:
		pcdevp-&gt;led = 1;
		break;
	case LED_IOCTL_OFF:
		pcdevp-&gt;led = 0;
		break;
	default:
		printk(KERN_ALERT "CharDeviceDriver: unknown ioctl command !\n");
		return -EFAULT;
	}
	chardevicedriver_led_control( index, pcdevp );
	return ret;
}

static int chardevicedriver_release(struct inode *inode, struct file *filp)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_release !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);
gpio_free(led_gpio_table[0]);
	return 0;
}

static struct file_operations chardevicedriver_fops = {
	.owner	= THIS_MODULE,
	.open	= chardevicedriver_open,
	.read	= chardevicedriver_read,
	.write	= chardevicedriver_write,
	.ioctl	= chardevicedriver_ioctl,
	.release= chardevicedriver_release,
};


// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;
	
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

	// register device number
	if( chardevicedriver_major ) { // static device number
		dev = MKDEV( chardevicedriver_major, chardevicedriver_minor );
		ret = register_chrdev_region( dev, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	}
	else { // dynamic device number
		ret = alloc_chrdev_region( &amp;dev, chardevicedriver_minor, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
		chardevicedriver_major = MAJOR( dev );
	}
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", chardevicedriver_major);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: Device Major = %d !\n", chardevicedriver_major);

	// allocate memory for private struct including struct cdev
	chardevicedriver_cdevp = kmalloc( sizeof( struct chardevicedriver_cdev ) * CHARDEVICEDRIVER_COUNT, GFP_KERNEL );
	if( IS_ERR( chardevicedriver_cdevp ) ) {
		printk(KERN_ALERT "CharDeviceDriver: No enough memory for private struct !\n");
		ret = PTR_ERR( chardevicedriver_cdevp );
		goto failure_alloc_cdev;
	}
	memset( chardevicedriver_cdevp, 0, sizeof( struct chardevicedriver_cdev ) * CHARDEVICEDRIVER_COUNT );
      cdev_init(&amp;(chardevicedriver_cdevp-&gt;cdev), &amp;chardevicedriver_fops );
	ret = cdev_add(&amp;(chardevicedriver_cdevp-&gt;cdev), dev, CHARDEVICEDRIVER_COUNT );
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Failure to add cdev to kernel, return value = %d !\n", ret);
		goto failure_add_cdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to add cdev to kernel ! Major: %d\tMinor: %d !\n", MAJOR( dev ), MINOR( dev ));

	return ret;

failure_add_cdev:
       kfree( chardevicedriver_cdevp );
failure_alloc_cdev:
	      unregister_chrdev_region( dev, CHARDEVICEDRIVER_COUNT );
failure_register_chrdev:
	      return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	int i = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");

	// destroy device and delete cdev object
	for( i = 0; i &lt; CHARDEVICEDRIVER_COUNT; i++ ) {
		cdev_del( &amp;( chardevicedriver_cdevp[ i ].cdev ) );
	}

 	// free memory for private struct
	kfree( chardevicedriver_cdevp );
	chardevicedriver_cdevp = NULL;

	// unregister device number
	unregister_chrdev_region( MKDEV( chardevicedriver_major, chardevicedriver_minor ), CHARDEVICEDRIVER_COUNT );
	printk(KERN_ALERT "CharDeviceDriver: Exit chardevicedriver_exit !\n");
}

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">3.编写testchardevicedriver1.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>testchardevicedriver1<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   testchardevicedriver1.c
</pre></div></div>
    <p>testchardevicedriver1.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>stdio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>stdlib<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>fcntl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>sys<span class="sh_symbol">/</span>ioctl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_string">"chardevicedriverioctlled.h"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> fd<span class="sh_symbol">;</span></li><li><span class="sh_type">char</span> ch<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">(</span><span class="sh_type">int</span> argc<span class="sh_symbol">,</span> <span class="sh_type">char</span> <span class="sh_symbol">**</span>argv<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver0"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Failure to open device file: /dev/chardevicedriver0 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">exit</span><span class="sh_symbol">(</span> <span class="sh_symbol">-</span><span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to open device file: /dev/chardevicedriver0 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">while</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Starting to test device: /dev/chardevicedriver0... </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"</span><span class="sh_specialchar">\t</span><span class="sh_string">1. Press key </span><span class="sh_specialchar">\'</span><span class="sh_string">n</span><span class="sh_specialchar">\'</span><span class="sh_string"> to Light on LED1 </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"</span><span class="sh_specialchar">\t</span><span class="sh_string">2. Press key </span><span class="sh_specialchar">\'</span><span class="sh_string">f</span><span class="sh_specialchar">\'</span><span class="sh_string"> to Light off LED1 </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"</span><span class="sh_specialchar">\t</span><span class="sh_string">3. Press key </span><span class="sh_specialchar">\'</span><span class="sh_string">q</span><span class="sh_specialchar">\'</span><span class="sh_string"> to exit... </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ch <span class="sh_symbol">=</span> <span class="sh_function">getchar</span><span class="sh_symbol">();</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">getchar</span><span class="sh_symbol">();</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_string">'q'</span> <span class="sh_symbol">==</span> ch <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">switch</span><span class="sh_symbol">(</span> ch <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> <span class="sh_string">'n'</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">ioctl</span><span class="sh_symbol">(</span> fd<span class="sh_symbol">,</span> LED_IOCTL_ON<span class="sh_symbol">,</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"LED1 should light on !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> <span class="sh_string">'f'</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">ioctl</span><span class="sh_symbol">(</span> fd<span class="sh_symbol">,</span> LED_IOCTL_OFF<span class="sh_symbol">,</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"LED1 should light off !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">default</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">sleep</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">close</span><span class="sh_symbol">(</span> fd <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to test device: /dev/chardevicedriver0 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;

#include &lt;sys/ioctl.h&gt;

#include "chardevicedriverioctlled.h"

int fd;
char ch;

int main(int argc, char **argv)
{
	fd = open( "/dev/chardevicedriver", O_RDWR );
	if( 0 &gt; fd ) {
		fd = open( "/dev/chardevicedriver0", O_RDWR );
	}
	if( 0 &gt; fd ) {
		printf("Failure to open device file: /dev/chardevicedriver0 !\n");
		exit( -1 );
	}
	printf("Success to open device file: /dev/chardevicedriver0 !\n");

	while( 1 ) {
		printf("Starting to test device: /dev/chardevicedriver0... \n");
		printf("\t1. Press key \'n\' to Light on LED1 \n");
		printf("\t2. Press key \'f\' to Light off LED1 \n");
		printf("\t3. Press key \'q\' to exit... \n");

		ch = getchar();
		getchar();

		if( 'q' == ch ) {
			break;
		}

		switch( ch ) {
		case 'n':
			ioctl( fd, LED_IOCTL_ON, 0 );
			printf("LED1 should light on !\n");
			break;
		case 'f':
			ioctl( fd, LED_IOCTL_OFF, 0 );
			printf("LED1 should light off !\n");
			break;
		default:
			break;
		}

		sleep( 1 );
	}

	close( fd );
	printf("Success to test device: /dev/chardevicedriver0 !\n");

	return 0;
}

</pre></div></div>
    <p class="number">4.编写Makefile文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li># makefile <span class="sh_keyword">for</span> kernel module</li><li><span style="display:none;">&nbsp;</span></li><li>MODNAME <span class="sh_symbol">=</span> chardevicedriver</li><li>CROSS_COMPILE <span class="sh_symbol">=</span> arm<span class="sh_symbol">-</span>linux<span class="sh_symbol">-</span></li><li>TESTPRE&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> test</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">ifeq</span> <span class="sh_symbol">(</span>$<span class="sh_symbol">(</span>PLATFORM<span class="sh_symbol">),</span> PC<span class="sh_symbol">)</span></li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>lib<span class="sh_symbol">/</span>modules<span class="sh_symbol">/</span>$<span class="sh_symbol">(</span><span class="sh_usertype">shell</span><span class="sh_normal"> </span>uname <span class="sh_symbol">-</span>r<span class="sh_symbol">)/</span>build</li><li><span class="sh_keyword">else</span></li><li>CC <span class="sh_symbol">=</span> $<span class="sh_symbol">(</span>CROSS_COMPILE<span class="sh_symbol">)</span>gcc</li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>tools<span class="sh_symbol">/</span>linux<span class="sh_number">-2.6.35.7</span></li><li>endif</li><li><span style="display:none;">&nbsp;</span></li><li>obj<span class="sh_symbol">-</span>m <span class="sh_symbol">:=</span> $<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>o</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">default</span><span class="sh_symbol">:</span> test driver</li><li><span style="display:none;">&nbsp;</span></li><li>test<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>CC<span class="sh_symbol">)</span> $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">1</span><span class="sh_symbol">.</span>c <span class="sh_symbol">-</span>o $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">1</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>driver<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>MAKE<span class="sh_symbol">)</span> <span class="sh_symbol">-</span>C $<span class="sh_symbol">(</span>KERNELDIR<span class="sh_symbol">)</span> M<span class="sh_symbol">=</span>$<span class="sh_symbol">(</span>PWD<span class="sh_symbol">)</span> modules</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>clean<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>f $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">1</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>rf <span class="sh_symbol">*.</span>o <span class="sh_symbol">*.</span>ko <span class="sh_symbol">*.</span>mod<span class="sh_symbol">.*</span> <span class="sh_symbol">.</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).*</span> <span class="sh_symbol">.</span>tmp<span class="sh_symbol">*</span> module<span class="sh_symbol">*</span> Module<span class="sh_symbol">*</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;"># makefile for kernel module

MODNAME = chardevicedriver
CROSS_COMPILE = arm-linux-
TESTPRE	= test

ifeq ($(PLATFORM), PC)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
else
CC = $(CROSS_COMPILE)gcc
KERNELDIR ?= /home/tarena/workdir/tools/linux-2.6.35.7
endif

obj-m := $(MODNAME).o

default: test driver

test:
	@echo "Compiling test program..."
	$(CC) $(TESTPRE)$(MODNAME)1.c -o $(TESTPRE)$(MODNAME)1
	@echo

driver:
	@echo "Compiling device driver..."
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@echo

clean:
	@echo "Cleanup test program..."
	@rm -f $(TESTPRE)$(MODNAME)1
	@echo
	@echo "Cleanup device driver..."
	@rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
	@echo
</pre></div></div>
    <p class="number">5.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver1文件拷贝到指定目录下，执行如下命令。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span><span class="sh_usertype">ko</span><span class="sh_normal">  </span>testchardevicedriver1   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko  testchardevicedriver1   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">6.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  insmod   chardevicedriver.ko
</pre></div></div>
    <p class="number">7.根据动态分配的主次设备号，手动创建设备文件节点，如图-12所示。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#   mknod  <span class="sh_symbol">/</span>dev<span class="sh_symbol">/</span>chardevicedriver1   c    <span class="sh_number">251</span>   <span class="sh_number">0</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#   mknod  /dev/chardevicedriver1   c    251   0
</pre></div></div>
    <div class="image">
      <img src="image012.png">
      <p>图-12</p>
    </div>
    <p class="number">8.运行应用测试程序，测试驱动程序。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_symbol">./</span> testchardevicedriver1</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  ./ testchardevicedriver1
</pre></div></div>
    <p>测试程序运行过程中，如图-13所示，输入n，则点亮TPAD上的LED1，并将cmd命令提取的各字段显示如下：cmd = 0x    6c80, ioctype = 0x      6c, iocnr = 0x      80, iocdir = 0x       0, iocsize = 0x       0！</p>
    <p>输入f，则熄灭TAD上的LED1。并将cmd命令提取的各字段显示如下： cmd = 0x    6c81, ioctype = 0x      6c, iocnr = 0x      81, iocdir = 0x       0, iocsize = 0x       0 !</p>
    <div class="image">
      <img src="image013.png">
      <p>图-13</p>
    </div>
    <h3>4.4 扩展</h3>
    <a name="case5">
    </a>
    <h2>5 按键驱动 V 1.5</h2>
    <h3>5.1 问题</h3>
    <p>在按键的驱动程序中，实现自动创建设备文件节点的功能。</p>
    <h3>5.2 方案</h3>
    <p class="number">一、如何自动创建设备节点。</p>
    <p>编写Linux设备驱动程序的时候，很多时候都是利用mknod [OPTION] NAME TYPE [MAJOR MINOR]命令手动创建设备节点，这种方式创建设备节点，在实际的驱动程序开发过程中，用的已经比较少了。那么是否有方法，能自动创建设备节点呢？</p>
    <p>其实，Linux内核为我们提供了一组函数，可以用来在模块加载的时候自动在/dev目录下创建相应设备节点，并在卸载模块时删除该节点，当然前提条件是用户空间移植了mdev（mdev）。</p>
    <p>内核中定义了struct class结构体，顾名思义，一个struct class结构体类型变量对应一个类，内核同时提供了class_create(…)函数，可以用它来创建一个类，这个类存放于sysfs下面，一旦创建好了这个类，再调用device_create(…)函数来在/dev目录下创建相应的设备节点。这样，加载模块的时候，用户空间中的mdev会自动响应device_create(…)函数，去/sysfs下寻找对应的类，从而创建设备节点。</p>
    <p>需要指出的是，mdev是应用层的，不要试图在内核的配置选项里找到它。加入对mdev的支持很简单，以一个字符设备驱动为例，在驱动初始化的代码里调用class_create为该设备创建一个class，再为每个设备调用device_create创建对应的设备。大致用法如下：</p>
    <p>struct class *myclass ；</p>
    <p>class_create(THIS_MODULE, “my_device_driver”);</p>
    <p>device_create(myclass, NULL, MKDEV(major_num, minor_num), NULL, “my_device”);</p>
    <p class="number">1．自动创建设备节点需要使用的几个函数的原型如下。</p>
    <p class="number">（1）class_create函数原型。</p>
    <p>struct class *class_create(struct module *owner, const char *name);</p>
    <p>owner: 创建设备类的驱动模块拥有者</p>
    <p>name: 待创建的设备类的类名称</p>
    <p>返回: 创建好的设备类的指针，失败返回NULL</p>
    <p class="number">（2）class_destroy函数原型。</p>
    <p>extern void class_destroy(struct class *cls);</p>
    <p class="number">（3）device_create函数原型。</p>
    <p>struct device *device_create(struct class *class, struct device *parent, dev_t devt, void *drvdata, const char *fmt, ...);</p>
    <p>class: 待创建的设备所属设备类</p>
    <p>parent: 指向可能存在的父设备的指针</p>
    <p>devt: 待创建设备的设备号(包括主设备号和次设备号)</p>
    <p>drvdata: 设备保留的驱动私有数据指针</p>
    <p>fmt: 待创建的设备文件名称</p>
    <p>返回: 创建好的device的指针，失败返回NULL</p>
    <p class="number">（4）device_destroy函数原型。</p>
    <p>extern void device_destroy(struct class *cls, dev_t devt);</p>
    <p class="number">2.mdev。</p>
    <p>mdev是busybox自带的一个简化版的udev，适合于嵌入式的应用场合，其具有使用简单的特点。它的作用，就是在系统启动和热插拔或动态加载驱动程序时，自动产生驱动程序所需的节点文件。</p>
    <p>在以busybox为基础构建嵌入式linux的根文件系统时，使用它是最优的选择。这需要在配置busybox的编译选项上添加对mdev的支持，如图-14所示。</p>
    <div class="image">
      <img src="image014.png">
      <p>图-14</p>
    </div>
    <p>其次，需要在启动脚本中，加入如下设置：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>mount <span class="sh_symbol">-</span>t <span class="sh_usertype">proc</span><span class="sh_normal"> </span>proc <span class="sh_symbol">/</span>proc</li><li>mount <span class="sh_symbol">-</span>t <span class="sh_usertype">sysfs</span><span class="sh_normal"> </span>sysfs <span class="sh_symbol">/</span>sys</li><li>echo <span class="sh_symbol">/</span>sbin<span class="sh_symbol">/</span>mdev <span class="sh_symbol">&gt;</span> <span class="sh_symbol">/</span>proc<span class="sh_symbol">/</span>sys<span class="sh_symbol">/</span>kernel<span class="sh_symbol">/</span>hotplug</li><li>mdev <span class="sh_symbol">-</span>s</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">mount -t proc proc /proc
mount -t sysfs sysfs /sys
echo /sbin/mdev &gt; /proc/sys/kernel/hotplug
mdev -s
</pre></div></div>
    <p class="number">二、本案例的操作步骤如下。</p>
    <p class="number">1.修改chardevicedriver.c源文件，实现自动创建设备文件节点的功能。</p>
    <p>（1）定义宏类名CHARDEVICEDRIVER_CLASS_NAME为chardevicedriver_class；</p>
    <p>（2）在设备结构体chardevicedriver_cdev中加入一个新的成员变量，设备结构体struct device *dev_device；</p>
    <p>（3）定义结构体class类型的指针变量*dev_class；</p>
    <p>（4）在chardevicedriver_init（）函数中，使用class_create（）函数创建一个名为CHARDEVICEDRIVER_CLASS_NAME的类，创建的该类会在/sys/class/目录下，并将创建好的类赋值给变量dev_class；</p>
    <p>（5）在chardevicedriver_init（）函数中，使用device_create（）函数创建一个设备文件，并赋值给chardevicedriver_cdevp-&gt;dev_device，大家需要注意的是，此函数并不会现在就创建对应的设备文件，而是在此驱动程序被加载时，用户空间mdev就会自动在/dev下创建chardevicedriver0这个设备文件；</p>
    <p>（6）在chardevicedriver_exit（）函数中，使用device_destroy（）函数销毁设备文件节点，使用 class_destroy（）函数销毁对应的设备类；</p>
    <p class="number">2.编写testchardevicedriver1.c源文件。</p>
    <p class="number">3.编写Makefile文件。</p>
    <p class="number">4.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver1文件拷贝到指定目录 。</p>
    <p class="number">5.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p class="number">6.运行应用测试程序，测试驱动程序。</p>
    <h3>5.3 实现</h3>
    <p class="number">1.继续使用按键驱动V1.4的chardevicedriverioctlled.h头文件。</p>
    <p class="number">2.修改chardevicedriver.c源文件，实现自动创建设备文件节点的功能。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>device<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>plat<span class="sh_symbol">/</span>gpio<span class="sh_symbol">-</span>cfg<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>slab<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_string">"chardevicedriverioctlled.h"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// licensed under BSD/GPL</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">1</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_CLASS_NAME&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver_class"</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_major <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_minor <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_cbracket">{</span></li><li>       <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">device</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>dev_device<span class="sh_symbol">;</span></li><li>       struct <span class="sh_usertype">cdev</span><span class="sh_normal"> </span>cdev<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">u8</span><span class="sh_normal"> </span>led<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_keyword">class</span> <span class="sh_symbol">*</span>dev_class <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>chardevicedriver_cdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> unsigned <span class="sh_type">long</span> led_gpio_table<span class="sh_symbol">[</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">]</span> <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>    <span class="sh_function">S5PV210_GPC1</span><span class="sh_symbol">(</span><span class="sh_number">3</span><span class="sh_symbol">),</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> <span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span><span class="sh_type">int</span> index<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">gpio_direction_output</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">s3c_gpio_setpull</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> S3C_GPIO_PULL_NONE <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">gpio_set_value</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_open</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// struct inode:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//  &nbsp;&nbsp;&nbsp;&nbsp;dev_t i_rdev: device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//&nbsp;&nbsp;&nbsp;&nbsp;struct cdev *i_cdev: private cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// struc file:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//&nbsp;&nbsp;&nbsp;&nbsp;void *private_data;</span></li><li>        <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> index<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardeivcedriver_open !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;pcdevp <span class="sh_symbol">=</span> <span class="sh_function">container_of</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_cdev<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev<span class="sh_symbol">,</span> cdev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;filp<span class="sh_symbol">-&gt;</span>private_data <span class="sh_symbol">=</span> pcdevp<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;index <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_rdev <span class="sh_symbol">)</span> <span class="sh_symbol">-</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">gpio_request</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">0</span><span class="sh_symbol">],</span> <span class="sh_string">"GPC1_3"</span><span class="sh_symbol">))</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"gpio_request failed!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span> index<span class="sh_symbol">,</span> pcdevp <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_read</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_read !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_write</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_keyword">const</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_write !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_ioctl</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> unsigned <span class="sh_type">int</span> cmd<span class="sh_symbol">,</span> unsigned <span class="sh_type">long</span> arg<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> index <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_rdev <span class="sh_symbol">)</span> <span class="sh_symbol">-</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_ioctl !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// check device type</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> LED_IOCTL_MAGIC <span class="sh_symbol">!=</span> <span class="sh_function">_IOC_TYPE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: ioctype mismatch !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// check ioctl nr</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_symbol">(</span> LED_IOCTL_NR_MIN <span class="sh_symbol">&gt;</span> <span class="sh_function">_IOC_NR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">||</span> <span class="sh_symbol">(</span> LED_IOCTL_NR_MAX <span class="sh_symbol">&lt;</span> <span class="sh_function">_IOC_NR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: iocnr mismatch !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// check access_ok for user space memory</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> _IOC_READ <span class="sh_symbol">&amp;</span> <span class="sh_function">_IOC_DIR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_symbol">!</span><span class="sh_function">access_ok</span><span class="sh_symbol">(</span> VERIFY_WRITE<span class="sh_symbol">,</span> arg<span class="sh_symbol">,</span> <span class="sh_function">_IOC_SIZE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: cann't access to write user space memory !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> _IOC_WRITE <span class="sh_symbol">&amp;</span> <span class="sh_function">_IOC_DIR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_symbol">!</span><span class="sh_function">access_ok</span><span class="sh_symbol">(</span> VERIFY_READ<span class="sh_symbol">,</span> arg<span class="sh_symbol">,</span> <span class="sh_function">_IOC_SIZE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: cann't access to read user space memory !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// print all fields of cmd</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: cmd = 0x%8x, ioctype = 0x%8x, iocnr = 0x%8x, iocdir = 0x%8x, iocsize = 0x%8x !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> cmd<span class="sh_symbol">,</span> <span class="sh_function">_IOC_TYPE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">),</span> <span class="sh_function">_IOC_NR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">),</span> <span class="sh_function">_IOC_DIR</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">),</span> <span class="sh_function">_IOC_SIZE</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">));</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// handle ioctl command</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">switch</span><span class="sh_symbol">(</span> cmd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> LED_IOCTL_ON<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">=</span> <span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> LED_IOCTL_OFF<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">default</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: unknown ioctl command !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span> index<span class="sh_symbol">,</span> pcdevp <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_release</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_release !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li>        <span class="sh_function">gpio_free</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">0</span><span class="sh_symbol">]);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file_operations</span><span class="sh_normal"> </span>chardevicedriver_fops <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>owner&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> THIS_MODULE<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>open&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_open<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>read&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_read<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>write&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_write<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>ioctl&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_ioctl<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>release<span class="sh_symbol">=</span> chardevicedriver_release<span class="sh_symbol">,</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> chardevicedriver_major <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// static device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">register_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">else</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// dynamic device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">alloc_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>dev<span class="sh_symbol">,</span> chardevicedriver_minor<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_major <span class="sh_symbol">=</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// allocate memory for private struct including struct cdev</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_cdevp <span class="sh_symbol">=</span> <span class="sh_function">kmalloc</span><span class="sh_symbol">(</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_symbol">)</span> <span class="sh_symbol">*</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> GFP_KERNEL <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: No enough memory for private struct !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_alloc_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">memset</span><span class="sh_symbol">(</span> chardevicedriver_cdevp<span class="sh_symbol">,</span> <span class="sh_number">0</span><span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_symbol">)</span> <span class="sh_symbol">*</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device class</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;dev_class <span class="sh_symbol">=</span> <span class="sh_function">class_create</span><span class="sh_symbol">(</span> THIS_MODULE<span class="sh_symbol">,</span> CHARDEVICEDRIVER_CLASS_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't create a device class: %s !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> CHARDEVICEDRIVER_CLASS_NAME<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_create_class<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to create a device class: %s !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> CHARDEVICEDRIVER_CLASS_NAME<span class="sh_symbol">);</span></li><li> <span class="sh_function">cdev_init</span><span class="sh_symbol">(&amp;(</span>chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">),</span> <span class="sh_symbol">&amp;</span>chardevicedriver_fops <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">cdev_add</span><span class="sh_symbol">(&amp;(</span>chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">),</span> dev<span class="sh_symbol">,</span> <span class="sh_number">1</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Failure to add cdev to kernel, return value = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> ret<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_add_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to add cdev to kernel ! Major: %d</span><span class="sh_specialchar">\t</span><span class="sh_string">Minor: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">),</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li><span style="display:none;">&nbsp;</span></li><li>      </li><li> chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>dev_device <span class="sh_symbol">=</span> <span class="sh_function">device_create</span><span class="sh_symbol">(</span> dev_class<span class="sh_symbol">,</span> NULL<span class="sh_symbol">,</span> dev<span class="sh_symbol">,</span> NULL<span class="sh_symbol">,</span> <span class="sh_string">"chardevicedriver%d"</span><span class="sh_symbol">,</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>dev_device <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"Cann't create a device: /dev/chardevicedriver%d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp<span class="sh_symbol">-&gt;</span>dev_device <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"Success to create a device: /dev/chardevicedriver%d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li>       <span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_add_cdev<span class="sh_symbol">:</span></li><li>      <span class="sh_function">class_destroy</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">);</span></li><li>failure_create_class<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">kfree</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>failure_alloc_cdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>       </li><li> <span class="sh_comment">// destroy device</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">device_destroy</span><span class="sh_symbol">(</span> dev_class<span class="sh_symbol">,</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor  <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// destroy device and delete cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">for</span><span class="sh_symbol">(</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span> i <span class="sh_symbol">&lt;</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">;</span> i<span class="sh_symbol">++</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_del</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span> chardevicedriver_cdevp<span class="sh_symbol">[</span> i <span class="sh_symbol">].</span>cdev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// destroy device class;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">class_destroy</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li> <span class="sh_comment">// free memory for private struct</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">kfree</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_cdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Exit chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;linux/device.h&gt;

#include &lt;asm/uaccess.h&gt;

#include &lt;asm/gpio.h&gt;
#include &lt;plat/gpio-cfg.h&gt;
#include &lt;linux/slab.h&gt;

#include "chardevicedriverioctlled.h"

// licensed under BSD/GPL
MODULE_LICENSE("Dual BSD/GPL");

#define CHARDEVICEDRIVER_MAJOR		0
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		1
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"
#define CHARDEVICEDRIVER_CLASS_NAME	"chardevicedriver_class"
static u32 chardevicedriver_major = CHARDEVICEDRIVER_MAJOR;
static u32 chardevicedriver_minor = CHARDEVICEDRIVER_MINOR;

struct chardevicedriver_cdev {
       struct device *dev_device;
       struct cdev cdev;

	u8 led;
};

static struct class *dev_class = NULL;
static struct chardevicedriver_cdev *chardevicedriver_cdevp = NULL;

static unsigned long led_gpio_table[ CHARDEVICEDRIVER_COUNT ] = {
    S5PV210_GPC1(3),
};


static void chardevicedriver_led_control(int index, struct chardevicedriver_cdev *pcdevp)
{
	gpio_direction_output( led_gpio_table[ index ], 0 );
	s3c_gpio_setpull( led_gpio_table[ index ], S3C_GPIO_PULL_NONE );
	gpio_set_value( led_gpio_table[ index ], pcdevp-&gt;led );
}

static int chardevicedriver_open(struct inode *inode, struct file *filp)
{
	// struct inode:
	//  	dev_t i_rdev: device number
	//	struct cdev *i_cdev: private cdev object
	// struc file:
	//	void *private_data;
        struct chardevicedriver_cdev *pcdevp = NULL;
	int index;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardeivcedriver_open !\n");

	pcdevp = container_of( inode-&gt;i_cdev, struct chardevicedriver_cdev, cdev );
	filp-&gt;private_data = pcdevp;

	index = MINOR( inode-&gt;i_rdev ) - CHARDEVICEDRIVER_MINOR;
	
	if(gpio_request(led_gpio_table[0], "GPC1_3"))
	{
		printk(KERN_ALERT "gpio_request failed!\n");
		return -1;
	}
	chardevicedriver_led_control( index, pcdevp );

	return 0;
}

static ssize_t chardevicedriver_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_read !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	return 0;
}

static ssize_t chardevicedriver_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_write !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	return 0;
}

static int chardevicedriver_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;
	int ret = -EFAULT;
	int index = MINOR( inode-&gt;i_rdev ) - CHARDEVICEDRIVER_MINOR;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_ioctl !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	// check device type
	if( LED_IOCTL_MAGIC != _IOC_TYPE( cmd ) ) {
		printk(KERN_ALERT "CharDeviceDriver: ioctype mismatch !\n");
		return ret;
	}

	// check ioctl nr
	if( ( LED_IOCTL_NR_MIN &gt; _IOC_NR( cmd ) ) || ( LED_IOCTL_NR_MAX &lt; _IOC_NR( cmd ) ) ) {
		printk(KERN_ALERT "CharDeviceDriver: iocnr mismatch !\n");
		return ret;
	}

	// check access_ok for user space memory
	if( _IOC_READ &amp; _IOC_DIR( cmd ) ) {
		if( !access_ok( VERIFY_WRITE, arg, _IOC_SIZE( cmd ) ) ) {
			printk(KERN_ALERT "CharDeviceDriver: cann't access to write user space memory !\n");
			return ret;
		}
	}
	if( _IOC_WRITE &amp; _IOC_DIR( cmd ) ) {
		if( !access_ok( VERIFY_READ, arg, _IOC_SIZE( cmd ) ) ) {
			printk(KERN_ALERT "CharDeviceDriver: cann't access to read user space memory !\n");
			return ret;
		}
	}

	// print all fields of cmd
	printk(KERN_ALERT "CharDeviceDriver: cmd = 0x%8x, ioctype = 0x%8x, iocnr = 0x%8x, iocdir = 0x%8x, iocsize = 0x%8x !\n", cmd, _IOC_TYPE( cmd ), _IOC_NR( cmd ), _IOC_DIR( cmd ), _IOC_SIZE( cmd ));

	// handle ioctl command
	ret = 0;
	switch( cmd ) {
	case LED_IOCTL_ON:
		pcdevp-&gt;led = 1;
		break;
	case LED_IOCTL_OFF:
		pcdevp-&gt;led = 0;
		break;
	default:
		printk(KERN_ALERT "CharDeviceDriver: unknown ioctl command !\n");
		return -EFAULT;
	}
	chardevicedriver_led_control( index, pcdevp );

	return ret;
}

static int chardevicedriver_release(struct inode *inode, struct file *filp)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_release !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);
        gpio_free(led_gpio_table[0]);
	return 0;
}

static struct file_operations chardevicedriver_fops = {
	.owner	= THIS_MODULE,
	.open	= chardevicedriver_open,
	.read	= chardevicedriver_read,
	.write	= chardevicedriver_write,
	.ioctl	= chardevicedriver_ioctl,
	.release= chardevicedriver_release,
};


// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;
	
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

	// register device number
	if( chardevicedriver_major ) { // static device number
		dev = MKDEV( chardevicedriver_major, chardevicedriver_minor );
		ret = register_chrdev_region( dev, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	}
	else { // dynamic device number
		ret = alloc_chrdev_region( &amp;dev, chardevicedriver_minor, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
		chardevicedriver_major = MAJOR( dev );
	}
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", chardevicedriver_major);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: Device Major = %d !\n", chardevicedriver_major);

	// allocate memory for private struct including struct cdev
	chardevicedriver_cdevp = kmalloc( sizeof( struct chardevicedriver_cdev ) * CHARDEVICEDRIVER_COUNT, GFP_KERNEL );
	if( IS_ERR( chardevicedriver_cdevp ) ) {
		printk(KERN_ALERT "CharDeviceDriver: No enough memory for private struct !\n");
		ret = PTR_ERR( chardevicedriver_cdevp );
		goto failure_alloc_cdev;
	}
	memset( chardevicedriver_cdevp, 0, sizeof( struct chardevicedriver_cdev ) * CHARDEVICEDRIVER_COUNT );

	// register device class
	dev_class = class_create( THIS_MODULE, CHARDEVICEDRIVER_CLASS_NAME );
	if( IS_ERR( dev_class ) ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't create a device class: %s !\n", CHARDEVICEDRIVER_CLASS_NAME);
		ret = PTR_ERR( dev_class );
		goto failure_create_class;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to create a device class: %s !\n", CHARDEVICEDRIVER_CLASS_NAME);
 cdev_init(&amp;(chardevicedriver_cdevp-&gt;cdev), &amp;chardevicedriver_fops );
	ret = cdev_add(&amp;(chardevicedriver_cdevp-&gt;cdev), dev, 1);
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Failure to add cdev to kernel, return value = %d !\n", ret);
		goto failure_add_cdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to add cdev to kernel ! Major: %d\tMinor: %d !\n", MAJOR( dev ), MINOR( dev ));

      
 chardevicedriver_cdevp-&gt;dev_device = device_create( dev_class, NULL, dev, NULL, "chardevicedriver%d", MINOR( dev ) );
	if( IS_ERR( chardevicedriver_cdevp-&gt;dev_device ) ) {
		printk(KERN_ALERT "Cann't create a device: /dev/chardevicedriver%d !\n", MINOR( dev ));
		ret = PTR_ERR( chardevicedriver_cdevp-&gt;dev_device );
		return ret;
	}
	printk(KERN_ALERT "Success to create a device: /dev/chardevicedriver%d !\n", MINOR( dev ));
       return ret;

failure_add_cdev:
      class_destroy( dev_class );
failure_create_class:
	kfree( chardevicedriver_cdevp );
failure_alloc_cdev:
	unregister_chrdev_region( dev, CHARDEVICEDRIVER_COUNT );
failure_register_chrdev:
	return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	int i = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");
       
 // destroy device
	device_destroy( dev_class, MKDEV( chardevicedriver_major, chardevicedriver_minor  );

	// destroy device and delete cdev object
	for( i = 0; i &lt; CHARDEVICEDRIVER_COUNT; i++ ) {
		cdev_del( &amp;( chardevicedriver_cdevp[ i ].cdev ) );
	}

// destroy device class;
	class_destroy( dev_class );

 // free memory for private struct
	kfree( chardevicedriver_cdevp );
	chardevicedriver_cdevp = NULL;

	// unregister device number
	unregister_chrdev_region( MKDEV( chardevicedriver_major, chardevicedriver_minor ), CHARDEVICEDRIVER_COUNT );
	printk(KERN_ALERT "CharDeviceDriver: Exit chardevicedriver_exit !\n");
}

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">3.修改testchardevicedriver1.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>testchardevicedriver1<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   testchardevicedriver1.c
</pre></div></div>
    <p>testchardevicedriver1.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>stdio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>stdlib<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>fcntl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>sys<span class="sh_symbol">/</span>ioctl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_string">"chardevicedriverioctlled.h"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> fd<span class="sh_symbol">;</span></li><li><span class="sh_type">char</span> ch<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">(</span><span class="sh_type">int</span> argc<span class="sh_symbol">,</span> <span class="sh_type">char</span> <span class="sh_symbol">**</span>argv<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>        fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver0"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Failure to open device file: /dev/chardevicedriver0 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">exit</span><span class="sh_symbol">(</span> <span class="sh_symbol">-</span><span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to open device file: /dev/chardevicedriver0 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">while</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Starting to test device: /dev/chardevicedriver0... </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"</span><span class="sh_specialchar">\t</span><span class="sh_string">1. Press key </span><span class="sh_specialchar">\'</span><span class="sh_string">n</span><span class="sh_specialchar">\'</span><span class="sh_string"> to Light on LED1 </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"</span><span class="sh_specialchar">\t</span><span class="sh_string">2. Press key </span><span class="sh_specialchar">\'</span><span class="sh_string">f</span><span class="sh_specialchar">\'</span><span class="sh_string"> to Light off LED1 </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"</span><span class="sh_specialchar">\t</span><span class="sh_string">3. Press key </span><span class="sh_specialchar">\'</span><span class="sh_string">q</span><span class="sh_specialchar">\'</span><span class="sh_string"> to exit... </span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ch <span class="sh_symbol">=</span> <span class="sh_function">getchar</span><span class="sh_symbol">();</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">getchar</span><span class="sh_symbol">();</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_string">'q'</span> <span class="sh_symbol">==</span> ch <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">switch</span><span class="sh_symbol">(</span> ch <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> <span class="sh_string">'n'</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">ioctl</span><span class="sh_symbol">(</span> fd<span class="sh_symbol">,</span> LED_IOCTL_ON<span class="sh_symbol">,</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"LED1 should light on !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">case</span> <span class="sh_string">'f'</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">ioctl</span><span class="sh_symbol">(</span> fd<span class="sh_symbol">,</span> LED_IOCTL_OFF<span class="sh_symbol">,</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"LED1 should light off !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">default</span><span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">break</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">sleep</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">close</span><span class="sh_symbol">(</span> fd <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to test device: /dev/chardevicedriver1 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;

#include &lt;sys/ioctl.h&gt;

#include "chardevicedriverioctlled.h"

int fd;
char ch;

int main(int argc, char **argv)
{
        fd = open( "/dev/chardevicedriver0", O_RDWR );
	if( 0 &gt; fd ) {
		printf("Failure to open device file: /dev/chardevicedriver0 !\n");
		exit( -1 );
	}
	printf("Success to open device file: /dev/chardevicedriver0 !\n");

	while( 1 ) {
		printf("Starting to test device: /dev/chardevicedriver0... \n");
		printf("\t1. Press key \'n\' to Light on LED1 \n");
		printf("\t2. Press key \'f\' to Light off LED1 \n");
		printf("\t3. Press key \'q\' to exit... \n");

		ch = getchar();
		getchar();

		if( 'q' == ch ) {
			break;
		}

		switch( ch ) {
		case 'n':
			ioctl( fd, LED_IOCTL_ON, 0 );
			printf("LED1 should light on !\n");
			break;
		case 'f':
			ioctl( fd, LED_IOCTL_OFF, 0 );
			printf("LED1 should light off !\n");
			break;
		default:
			break;
		}

		sleep( 1 );
	}

	close( fd );
	printf("Success to test device: /dev/chardevicedriver1 !\n");

	return 0;
}
</pre></div></div>
    <p class="number">4.继续使用按键驱动 V1.4中的Makefile文件。</p>
    <p class="number">5.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver1文件拷贝到指定目录下，执行如下命令。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span><span class="sh_usertype">ko</span><span class="sh_normal">  </span>testchardevicedriver1   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko  testchardevicedriver1   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">6.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li><li><span class="sh_symbol">/</span>#  ls   <span class="sh_symbol">/</span>dev<span class="sh_symbol">/</span>   <span class="sh_symbol">-</span>l</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  insmod   chardevicedriver.ko
/#  ls   /dev/   -l
</pre></div></div>
    <p>运行加载驱动的命令之后，查看TPAD的/dev目录，程序已经自动在该目录下创建设备文件/dev/chardevicedriver0，如图-15所示。</p>
    <div class="image">
      <img src="image015.png">
      <p>图-15</p>
    </div>
    <p class="number">7.运行应用测试程序，测试驱动程序。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_symbol">./</span> testchardevicedriver1</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  ./ testchardevicedriver1
</pre></div></div>
    <p>测试程序运行过程中，如图-16所示，输入n，则点亮TPAD上的LED1，输入f，则熄灭TAD上的LED1。</p>
    <div class="image">
      <img src="image016.png">
      <p>图-16</p>
    </div>
    <h3>5.4 扩展</h3>
    <a name="case6">
    </a>
    <h2>6 多个设备个体实验</h2>
    <h3>6.1 问题</h3>
    <p>编写一个驱动程序，可以支持多个主设备号相同，次设备号不同的设备的使用。</p>
    <h3>6.2 方案</h3>
    <p class="number">一、如何让一个驱动程序支持多个设备。</p>
    <p>为设备驱动支持多个设备个体，必须对驱动进行改进。循环调用为每个设备添加cdev对象和创建设备节点而封装的独立函数，以实现在系统中添加对多个设备个体的支持。</p>
    <p>该独立函数定义为：</p>
    <p>static int chardevicedriver_cdev_add(struct chardevicedriver_cdev *pcdevp, int index)</p>
    <p>函数功能：</p>
    <p>要向内核添加几个主设备号相同的设备，就需要调用几次该函数。该函数用来初始化cdev结构体，并向内核添加cdev结构体，之后为添加进内核的设备，根据不同的设备号（主设备号相同，次设备号不同）创建不同的设备文件节点，当然，此操作是在加载该驱动模块时，由用户空间的mdev来创建设备文件节点。</p>
    <p>函数参数：</p>
    <p>pcdevp: 重新定义的设备结构体，包含cdev基本的设备结构体；</p>
    <p>index: 设备的数量，用于生成每个设备的次设备号。</p>
    <p class="number">二、本案例的操作步骤如下。</p>
    <p class="number">1.修改chardevicedriver.c源文件，实现驱动程序支持2个设备。</p>
    <p>（1）将定义的设备数量宏CHARDEVICEDRIVER_COUNT定义为2；</p>
    <p>（2）将定义的led_gpio_table[ CHARDEVICEDRIVER_COUNT ]数组中再增加一个GPIO管脚的描述S5PV210_GPC1(4)；</p>
    <p>（3）在chardevicedriver_open（）函数中，使用gpio_request（）函数申请KEY1UP、KEY2DOWN两个按键使用的GPIO管脚，led1、led2两个灯使用GPIO管脚；</p>
    <p>（4）获取设备的次设备号，区分是操作的哪盏led灯，调用chardevicedriver_led_control（）函数为该灯进行初始化；</p>
    <p>（5）在chardevicedriver_read（）函数中，实现如下步骤：</p>
    <p>1）定义chardevicedriver_cdev 类型的局部变量*pcdevp，被赋值为filp-&gt;private_data;</p>
    <p>2）根据获取到的不同的次设备号，区分不同的设备，获取相对应GPIO管脚的高低电平，赋值给变量key_value，并将该值拷贝至用户空间的buf；</p>
    <p>3）根据不同的key_value，返回1或0；</p>
    <p>（6）在chardevicedriver_write（）函数中，实现如下步骤：</p>
    <p>1）定义chardevicedriver_cdev 类型的局部变量*pcdevp，被赋值为filp-&gt;private_data;</p>
    <p>2）将用户空间buf的值赋值给pcdevp-&gt;led；</p>
    <p>3）获取设备的次设备号，区分是操作的哪盏led灯，调用chardevicedriver_led_control（）函数控制该灯的亮灭；</p>
    <p>4）在函数chardevicedriver_init（）中，调用chardevicedriver_cdev_add（）函数循环的添加设备到内核中；</p>
    <p>5）实现chardevicedriver_cdev_add（）函数，功能为循环添加设备到内核中，并为该设备创建设备文件；</p>
    <p>6）在函数chardevicedriver_exit（）中，释放所有申请到的GPIO管脚；</p>
    <p class="number">2.编写testchardevicedriver1.c、testchardevicedriver2.c源文件。</p>
    <p class="number">3.编写Makefile文件。</p>
    <p class="number">4.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver1、testchardevicedriver2文件拷贝到指定目录。</p>
    <p class="number">5.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p class="number">6.分别运行两个应用测试程序，测试驱动程序。</p>
    <h3>6.3 实现</h3>
    <p class="number">1.修改chardevicedriver.c源文件，实现驱动程序支持2个设备。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   chardevicedriver.c
</pre></div></div>
    <p>chardevicedriver.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap" style="display: none; "><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="hide sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>init<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>module<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>fs<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>cdev<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>device<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>uaccess<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>asm<span class="sh_symbol">/</span>gpio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>plat<span class="sh_symbol">/</span>gpio<span class="sh_symbol">-</span>cfg<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>linux<span class="sh_symbol">/</span>slab<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// licensed under BSD/GPL</span></li><li><span class="sh_function">MODULE_LICENSE</span><span class="sh_symbol">(</span><span class="sh_string">"Dual BSD/GPL"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MAJOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_MINOR&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">0</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_COUNT&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_number">2</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_NAME&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver"</span></li><li>#<span class="sh_usertype">define</span><span class="sh_normal"> </span>CHARDEVICEDRIVER_CLASS_NAME&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_string">"chardevicedriver_class"</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_major <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MAJOR<span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">u32</span><span class="sh_normal"> </span>chardevicedriver_minor <span class="sh_symbol">=</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">device</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>dev_device<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;struct <span class="sh_usertype">cdev</span><span class="sh_normal"> </span>cdev<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">u8</span><span class="sh_normal"> </span>led<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>chardevicedriver_cdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_keyword">class</span> <span class="sh_symbol">*</span>dev_class <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> unsigned <span class="sh_type">long</span> led_gpio_table<span class="sh_symbol">[</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">]</span> <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>    <span class="sh_function">S5PV210_GPC1</span><span class="sh_symbol">(</span><span class="sh_number">3</span><span class="sh_symbol">),</span></li><li>    <span class="sh_function">S5PV210_GPC1</span><span class="sh_symbol">(</span><span class="sh_number">4</span><span class="sh_symbol">),</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> <span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span><span class="sh_type">int</span> index<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">gpio_direction_output</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> <span class="sh_number">0</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">s3c_gpio_setpull</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> S3C_GPIO_PULL_NONE <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">gpio_set_value</span><span class="sh_symbol">(</span> led_gpio_table<span class="sh_symbol">[</span> index <span class="sh_symbol">],</span> pcdevp<span class="sh_symbol">-&gt;</span>led <span class="sh_symbol">);</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_open</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// struct inode:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//  &nbsp;&nbsp;&nbsp;&nbsp;dev_t i_rdev: device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//&nbsp;&nbsp;&nbsp;&nbsp;struct cdev *i_cdev: private cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// struc file:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">//&nbsp;&nbsp;&nbsp;&nbsp;void *private_data;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> index<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardeivcedriver_open !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;pcdevp <span class="sh_symbol">=</span> <span class="sh_function">container_of</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_cdev<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev<span class="sh_symbol">,</span> cdev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;filp<span class="sh_symbol">-&gt;</span>private_data <span class="sh_symbol">=</span> pcdevp<span class="sh_symbol">;</span></li><li> <span class="sh_keyword">if</span> <span class="sh_symbol">(</span><span class="sh_function">MINOR</span><span class="sh_symbol">(</span>inode<span class="sh_symbol">-&gt;</span>i_rdev<span class="sh_symbol">)</span> <span class="sh_symbol">==</span> <span class="sh_number">0</span><span class="sh_symbol">)</span><span class="sh_cbracket">{</span></li><li> <span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">gpio_request</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">),</span> <span class="sh_string">"Buttonup"</span><span class="sh_symbol">))</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"gpio_request failed!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>        </li><li> <span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">gpio_request</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">0</span><span class="sh_symbol">],</span><span class="sh_string">"GPC1_3"</span><span class="sh_symbol">))</span></li><li>        <span class="sh_cbracket">{</span></li><li>                <span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT<span class="sh_string">"gpio_request failed!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>                <span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>        <span class="sh_cbracket">}</span></li><li>        <span class="sh_cbracket">}</span></li><li>        <span class="sh_keyword">else</span></li><li>        <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">gpio_request</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">1</span><span class="sh_symbol">),</span> <span class="sh_string">"Buttondn"</span><span class="sh_symbol">))</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"gpio_request failed!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">gpio_request</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">1</span><span class="sh_symbol">],</span> <span class="sh_string">"GPC1_4"</span><span class="sh_symbol">))</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"gpio_request failed!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>        <span class="sh_cbracket">}</span></li><li>        index <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> inode<span class="sh_symbol">-&gt;</span>i_rdev<span class="sh_symbol">)</span> <span class="sh_symbol">-</span> CHARDEVICEDRIVER_MINOR<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span> index<span class="sh_symbol">,</span> pcdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_read</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_read !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>       unsigned <span class="sh_type">char</span> key_value<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">size_t</span><span class="sh_normal">  </span>cnt <span class="sh_symbol">=</span> count<span class="sh_symbol">;</span></li><li> <span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">MINOR</span><span class="sh_symbol">(</span>pcdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">.</span>dev<span class="sh_symbol">)</span> <span class="sh_symbol">==</span> <span class="sh_number">0</span><span class="sh_symbol">)</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;     key_value <span class="sh_symbol">=</span> <span class="sh_function">gpio_get_value</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">));</span></li><li> <span class="sh_keyword">else</span></li><li>      key_value <span class="sh_symbol">=</span> <span class="sh_function">gpio_get_value</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">1</span><span class="sh_symbol">));</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">copy_to_user</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>key_value<span class="sh_symbol">,</span> cnt<span class="sh_symbol">))</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>     <span class="sh_keyword">if</span> <span class="sh_symbol">(</span>key_value<span class="sh_symbol">)</span></li><li>       <span class="sh_keyword">return</span> <span class="sh_number">1</span><span class="sh_symbol">;</span></li><li> <span class="sh_keyword">if</span> <span class="sh_symbol">(!</span>key_value<span class="sh_symbol">)</span></li><li>       <span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">ssize_t</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_write</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> <span class="sh_keyword">const</span> <span class="sh_type">char</span> __<span class="sh_usertype">user</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>buf<span class="sh_symbol">,</span> <span class="sh_usertype">size_t</span><span class="sh_normal"> </span>count<span class="sh_symbol">,</span> <span class="sh_usertype">loff_t</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>f_pos<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span>      </li><li>       <span class="sh_type">int</span> index<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span class="sh_usertype">size_t</span><span class="sh_normal">  </span>cnt <span class="sh_symbol">=</span> count<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_write !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>       <span class="sh_keyword">if</span><span class="sh_symbol">(</span><span class="sh_function">copy_from_user</span><span class="sh_symbol">(&amp;(</span>pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">),</span>buf<span class="sh_symbol">,</span> cnt<span class="sh_symbol">))</span> <span class="sh_cbracket">{</span> </li><li>                <span class="sh_keyword">return</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>       <span class="sh_cbracket">}</span></li><li>       <span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"led =%d!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span>pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li>       index <span class="sh_symbol">=</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span>pcdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">.</span>dev<span class="sh_symbol">);</span></li><li>       <span class="sh_function">chardevicedriver_led_control</span><span class="sh_symbol">(</span>index<span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_ioctl</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">,</span> unsigned <span class="sh_type">int</span> cmd<span class="sh_symbol">,</span> unsigned <span class="sh_type">long</span> arg<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_ioctl !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_release</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">inode</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>inode<span class="sh_symbol">,</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>filp<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp <span class="sh_symbol">=</span> filp<span class="sh_symbol">-&gt;</span>private_data<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_release !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: LED: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> pcdevp<span class="sh_symbol">-&gt;</span>led<span class="sh_symbol">);</span></li><li>        <span class="sh_function">gpio_free</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">0</span><span class="sh_symbol">]);</span></li><li>        <span class="sh_function">gpio_free</span><span class="sh_symbol">(</span>led_gpio_table<span class="sh_symbol">[</span><span class="sh_number">1</span><span class="sh_symbol">]);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">file_operations</span><span class="sh_normal"> </span>chardevicedriver_fops <span class="sh_symbol">=</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>owner&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> THIS_MODULE<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>open&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_open<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>read&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_read<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>write&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_write<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>ioctl&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> chardevicedriver_ioctl<span class="sh_symbol">,</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">.</span>release<span class="sh_symbol">=</span> chardevicedriver_release<span class="sh_symbol">,</span></li><li><span class="sh_cbracket">}</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> <span class="sh_function">chardevicedriver_cdev_add</span><span class="sh_symbol">(</span><span class="sh_usertype">struct</span><span class="sh_normal"> </span><span class="sh_usertype">chardevicedriver_cdev</span><span class="sh_normal"> </span><span class="sh_symbol">*</span>pcdevp<span class="sh_symbol">,</span> <span class="sh_type">int</span> index<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_cdev_add !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">+</span> index <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_init</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span>pcdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">),</span> <span class="sh_symbol">&amp;</span>chardevicedriver_fops <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">cdev_add</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span>pcdevp<span class="sh_symbol">-&gt;</span>cdev<span class="sh_symbol">),</span> dev<span class="sh_symbol">,</span> <span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Failure to add cdev to kernel ! Major: %d</span><span class="sh_specialchar">\t</span><span class="sh_string">Minor: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">),</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to add cdev to kernel ! Major: %d</span><span class="sh_specialchar">\t</span><span class="sh_string">Minor: %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">),</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;pcdevp<span class="sh_symbol">-&gt;</span>dev_device <span class="sh_symbol">=</span> <span class="sh_function">device_create</span><span class="sh_symbol">(</span> dev_class<span class="sh_symbol">,</span> NULL<span class="sh_symbol">,</span> dev<span class="sh_symbol">,</span> NULL<span class="sh_symbol">,</span> <span class="sh_string">"chardevicedriver%d"</span><span class="sh_symbol">,</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> pcdevp<span class="sh_symbol">-&gt;</span>dev_device <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"Cann't create a device: /dev/chardevicedriver%d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> pcdevp<span class="sh_symbol">-&gt;</span>dev_device <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"Success to create a device: /dev/chardevicedriver%d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> <span class="sh_function">MINOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// initialize module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">int</span> __<span class="sh_usertype">init</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_init</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_symbol">-</span>EFAULT<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_usertype">dev_t</span><span class="sh_normal"> </span>dev <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> j <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_init !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> chardevicedriver_major <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// static device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;dev <span class="sh_symbol">=</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">register_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">else</span> <span class="sh_cbracket">{</span> <span class="sh_comment">// dynamic device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">alloc_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;</span>dev<span class="sh_symbol">,</span> chardevicedriver_minor<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> CHARDEVICEDRIVER_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_major <span class="sh_symbol">=</span> <span class="sh_function">MAJOR</span><span class="sh_symbol">(</span> dev <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_register_chrdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to register char device: Device Major = %d !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> chardevicedriver_major<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// allocate memory for private struct including struct cdev</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_cdevp <span class="sh_symbol">=</span> <span class="sh_function">kmalloc</span><span class="sh_symbol">(</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_symbol">)</span> <span class="sh_symbol">*</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">,</span> GFP_KERNEL <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: No enough memory for private struct !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_alloc_cdev<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">memset</span><span class="sh_symbol">(</span> chardevicedriver_cdevp<span class="sh_symbol">,</span> <span class="sh_number">0</span><span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span> <span class="sh_usertype">struct</span><span class="sh_normal"> </span>chardevicedriver_cdev <span class="sh_symbol">)</span> <span class="sh_symbol">*</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register device class</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;dev_class <span class="sh_symbol">=</span> <span class="sh_function">class_create</span><span class="sh_symbol">(</span> THIS_MODULE<span class="sh_symbol">,</span> CHARDEVICEDRIVER_CLASS_NAME <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_function">IS_ERR</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Cann't create a device class: %s !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> CHARDEVICEDRIVER_CLASS_NAME<span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">PTR_ERR</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_create_class<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Success to create a device class: %s !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> CHARDEVICEDRIVER_CLASS_NAME<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// register cdev object and device for creating device file</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">for</span><span class="sh_symbol">(</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span> i <span class="sh_symbol">&lt;</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">;</span> i<span class="sh_symbol">++</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ret <span class="sh_symbol">=</span> <span class="sh_function">chardevicedriver_cdev_add</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span>chardevicedriver_cdevp<span class="sh_symbol">[</span> i <span class="sh_symbol">]),</span> i <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> ret <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">goto</span> failure_cdev_add<span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"Success to add all cdev objects to kernel and create all device files !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>failure_cdev_add<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">for</span><span class="sh_symbol">(</span> j <span class="sh_symbol">=</span> i<span class="sh_symbol">;</span> j <span class="sh_symbol">&gt;=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span> j<span class="sh_symbol">--</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">device_destroy</span><span class="sh_symbol">(</span> dev_class<span class="sh_symbol">,</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> <span class="sh_symbol">(</span> chardevicedriver_minor <span class="sh_symbol">+</span> j <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_del</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span>chardevicedriver_cdevp<span class="sh_symbol">[</span> j <span class="sh_symbol">].</span>cdev<span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">class_destroy</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">);</span></li><li>failure_create_class<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">kfree</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>failure_alloc_cdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> dev<span class="sh_symbol">,</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li>failure_register_chrdev<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> ret<span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// clean up module function</span></li><li><span class="sh_keyword">static</span> <span class="sh_type">void</span> __<span class="sh_usertype">exit</span><span class="sh_normal"> </span><span class="sh_function">chardevicedriver_exit</span><span class="sh_symbol">(</span><span class="sh_type">void</span><span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_type">int</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Entry chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// destroy device and delete cdev object</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">for</span><span class="sh_symbol">(</span> i <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span> i <span class="sh_symbol">&lt;</span> CHARDEVICEDRIVER_COUNT<span class="sh_symbol">;</span> i<span class="sh_symbol">++</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">device_destroy</span><span class="sh_symbol">(</span> dev_class<span class="sh_symbol">,</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> <span class="sh_symbol">(</span> chardevicedriver_minor <span class="sh_symbol">+</span> i <span class="sh_symbol">)</span> <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">cdev_del</span><span class="sh_symbol">(</span> <span class="sh_symbol">&amp;(</span> chardevicedriver_cdevp<span class="sh_symbol">[</span> i <span class="sh_symbol">].</span>cdev <span class="sh_symbol">)</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// destroy device class;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">class_destroy</span><span class="sh_symbol">(</span> dev_class <span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// free memory for private struct</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">kfree</span><span class="sh_symbol">(</span> chardevicedriver_cdevp <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;chardevicedriver_cdevp <span class="sh_symbol">=</span> NULL<span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_comment">// unregister device number</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">unregister_chrdev_region</span><span class="sh_symbol">(</span> <span class="sh_function">MKDEV</span><span class="sh_symbol">(</span> chardevicedriver_major<span class="sh_symbol">,</span> chardevicedriver_minor <span class="sh_symbol">),</span> CHARDEVICEDRIVER_COUNT <span class="sh_symbol">);</span></li><li><span class="sh_function">gpio_free</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">0</span><span class="sh_symbol">));</span></li><li> <span class="sh_function">gpio_free</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPH0</span><span class="sh_symbol">(</span><span class="sh_number">1</span><span class="sh_symbol">));</span></li><li> <span class="sh_function">gpio_free</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPC1</span><span class="sh_symbol">(</span><span class="sh_number">3</span><span class="sh_symbol">));</span></li><li><span class="sh_function">gpio_free</span><span class="sh_symbol">(</span><span class="sh_function">S5PV210_GPC1</span><span class="sh_symbol">(</span><span class="sh_number">4</span><span class="sh_symbol">));</span></li><li> <span class="sh_function">printk</span><span class="sh_symbol">(</span>KERN_ALERT <span class="sh_string">"CharDeviceDriver: Exit chardevicedriver_exit !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_cbracket">}</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// the declarations of initialization and cleaning up module functions</span></li><li><span class="sh_function">module_init</span><span class="sh_symbol">(</span>chardevicedriver_init<span class="sh_symbol">);</span></li><li><span class="sh_function">module_exit</span><span class="sh_symbol">(</span>chardevicedriver_exit<span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_comment">// module information</span></li><li><span class="sh_function">MODULE_AUTHOR</span><span class="sh_symbol">(</span><span class="sh_string">"Tarena"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_DESCRIPTION</span><span class="sh_symbol">(</span><span class="sh_string">"My first char device driver to add device file operations"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_VERSION</span><span class="sh_symbol">(</span><span class="sh_string">"0.0.1"</span><span class="sh_symbol">);</span></li><li><span class="sh_function">MODULE_ALIAS</span><span class="sh_symbol">(</span><span class="sh_string">"CharDeviceDriver"</span><span class="sh_symbol">);</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;linux/init.h&gt;
#include &lt;linux/module.h&gt;

#include &lt;linux/fs.h&gt;
#include &lt;linux/cdev.h&gt;
#include &lt;linux/device.h&gt;

#include &lt;asm/uaccess.h&gt;

#include &lt;asm/gpio.h&gt;
#include &lt;plat/gpio-cfg.h&gt;
#include &lt;linux/slab.h&gt;

// licensed under BSD/GPL
MODULE_LICENSE("Dual BSD/GPL");

#define CHARDEVICEDRIVER_MAJOR		0
#define CHARDEVICEDRIVER_MINOR		0
#define CHARDEVICEDRIVER_COUNT		2
#define CHARDEVICEDRIVER_NAME		"chardevicedriver"
#define CHARDEVICEDRIVER_CLASS_NAME	"chardevicedriver_class"

static u32 chardevicedriver_major = CHARDEVICEDRIVER_MAJOR;
static u32 chardevicedriver_minor = CHARDEVICEDRIVER_MINOR;

struct chardevicedriver_cdev {
	struct device *dev_device;
	struct cdev cdev;

	u8 led;
};
static struct chardevicedriver_cdev *chardevicedriver_cdevp = NULL;

static struct class *dev_class = NULL;

static unsigned long led_gpio_table[ CHARDEVICEDRIVER_COUNT ] = {
    S5PV210_GPC1(3),
    S5PV210_GPC1(4),
};


static void chardevicedriver_led_control(int index, struct chardevicedriver_cdev *pcdevp)
{
	gpio_direction_output( led_gpio_table[ index ], 0 );
	s3c_gpio_setpull( led_gpio_table[ index ], S3C_GPIO_PULL_NONE );
	gpio_set_value( led_gpio_table[ index ], pcdevp-&gt;led );
}

static int chardevicedriver_open(struct inode *inode, struct file *filp)
{
	// struct inode:
	//  	dev_t i_rdev: device number
	//	struct cdev *i_cdev: private cdev object
	// struc file:
	//	void *private_data;
	struct chardevicedriver_cdev *pcdevp = NULL;
	int index;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardeivcedriver_open !\n");

	pcdevp = container_of( inode-&gt;i_cdev, struct chardevicedriver_cdev, cdev );
	filp-&gt;private_data = pcdevp;
 if (MINOR(inode-&gt;i_rdev) == 0){
 if(gpio_request(S5PV210_GPH0(0), "Buttonup"))
	{
		printk(KERN_ALERT "gpio_request failed!\n");
		return -1;
	}
        
 if(gpio_request(led_gpio_table[0],"GPC1_3"))
        {
                printk(KERN_ALERT"gpio_request failed!\n");
                return -1;
        }
        }
        else
        {
	if(gpio_request(S5PV210_GPH0(1), "Buttondn"))
	{
		printk(KERN_ALERT "gpio_request failed!\n");
		return -1;
	}
	
	if(gpio_request(led_gpio_table[1], "GPC1_4"))
	{
		printk(KERN_ALERT "gpio_request failed!\n");
		return -1;
	}
        }
        index = MINOR( inode-&gt;i_rdev) - CHARDEVICEDRIVER_MINOR;
	chardevicedriver_led_control( index, pcdevp );
	return 0;
}

static ssize_t chardevicedriver_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_read !\n");
       unsigned char key_value;
	size_t  cnt = count;
 if(MINOR(pcdevp-&gt;cdev.dev) == 0)
	     key_value = gpio_get_value(S5PV210_GPH0(0));
 else
      key_value = gpio_get_value(S5PV210_GPH0(1));

	if(copy_to_user(buf, &amp;key_value, cnt)) {
		return -EFAULT;
	}
     if (key_value)
       return 1;
 if (!key_value)
       return 0;
}

static ssize_t chardevicedriver_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{      
       int index;
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;
size_t  cnt = count;
	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_write !\n");

       if(copy_from_user(&amp;(pcdevp-&gt;led),buf, cnt)) { 
                return -EFAULT;
       }
       printk(KERN_ALERT "led =%d!\n",pcdevp-&gt;led);
       index = MINOR(pcdevp-&gt;cdev.dev);
       chardevicedriver_led_control(index, pcdevp);
	return 0;
}

static int chardevicedriver_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_ioctl !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);

	return 0;
}

static int chardevicedriver_release(struct inode *inode, struct file *filp)
{
	struct chardevicedriver_cdev *pcdevp = filp-&gt;private_data;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_release !\n");

	printk(KERN_ALERT "CharDeviceDriver: LED: %d !\n", pcdevp-&gt;led);
        gpio_free(led_gpio_table[0]);
        gpio_free(led_gpio_table[1]);

	return 0;
}

static struct file_operations chardevicedriver_fops = {
	.owner	= THIS_MODULE,
	.open	= chardevicedriver_open,
	.read	= chardevicedriver_read,
	.write	= chardevicedriver_write,
	.ioctl	= chardevicedriver_ioctl,
	.release= chardevicedriver_release,
};

static int chardevicedriver_cdev_add(struct chardevicedriver_cdev *pcdevp, int index)
{
	int ret = -EFAULT;
	dev_t dev = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_cdev_add !\n");

	dev = MKDEV( chardevicedriver_major, chardevicedriver_minor + index );
	cdev_init( &amp;(pcdevp-&gt;cdev), &amp;chardevicedriver_fops );
	ret = cdev_add( &amp;(pcdevp-&gt;cdev), dev, 1 );
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Failure to add cdev to kernel ! Major: %d\tMinor: %d !\n", MAJOR( dev ), MINOR( dev ));
		return ret;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to add cdev to kernel ! Major: %d\tMinor: %d !\n", MAJOR( dev ), MINOR( dev ));

	pcdevp-&gt;dev_device = device_create( dev_class, NULL, dev, NULL, "chardevicedriver%d", MINOR( dev ) );
	if( IS_ERR( pcdevp-&gt;dev_device ) ) {
		printk(KERN_ALERT "Cann't create a device: /dev/chardevicedriver%d !\n", MINOR( dev ));
		ret = PTR_ERR( pcdevp-&gt;dev_device );
		return ret;
	}
	printk(KERN_ALERT "Success to create a device: /dev/chardevicedriver%d !\n", MINOR( dev ));
	return 0;
}

// initialize module function
static int __init chardevicedriver_init(void)
{
	int ret = -EFAULT;
	dev_t dev = 0;
	int i = 0;
	int j = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_init !\n");

	// register device number
	if( chardevicedriver_major ) { // static device number
		dev = MKDEV( chardevicedriver_major, chardevicedriver_minor );
		ret = register_chrdev_region( dev, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
	}
	else { // dynamic device number
		ret = alloc_chrdev_region( &amp;dev, chardevicedriver_minor, CHARDEVICEDRIVER_COUNT, CHARDEVICEDRIVER_NAME );
		chardevicedriver_major = MAJOR( dev );
	}
	if( 0 &gt; ret ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't register char device: Device Major = %d !\n", chardevicedriver_major);
		goto failure_register_chrdev;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to register char device: Device Major = %d !\n", chardevicedriver_major);

	// allocate memory for private struct including struct cdev
	chardevicedriver_cdevp = kmalloc( sizeof( struct chardevicedriver_cdev ) * CHARDEVICEDRIVER_COUNT, GFP_KERNEL );
	if( IS_ERR( chardevicedriver_cdevp ) ) {
		printk(KERN_ALERT "CharDeviceDriver: No enough memory for private struct !\n");
		ret = PTR_ERR( chardevicedriver_cdevp );
		goto failure_alloc_cdev;
	}
	memset( chardevicedriver_cdevp, 0, sizeof( struct chardevicedriver_cdev ) * CHARDEVICEDRIVER_COUNT );

	// register device class
	dev_class = class_create( THIS_MODULE, CHARDEVICEDRIVER_CLASS_NAME );
	if( IS_ERR( dev_class ) ) {
		printk(KERN_ALERT "CharDeviceDriver: Cann't create a device class: %s !\n", CHARDEVICEDRIVER_CLASS_NAME);
		ret = PTR_ERR( dev_class );
		goto failure_create_class;
	}
	printk(KERN_ALERT "CharDeviceDriver: Success to create a device class: %s !\n", CHARDEVICEDRIVER_CLASS_NAME);

	// register cdev object and device for creating device file
	for( i = 0; i &lt; CHARDEVICEDRIVER_COUNT; i++ ) {
		ret = chardevicedriver_cdev_add( &amp;(chardevicedriver_cdevp[ i ]), i );
		if( 0 &gt; ret ) {
			goto failure_cdev_add;
		}
	}
	printk(KERN_ALERT "Success to add all cdev objects to kernel and create all device files !\n");

	return ret;

failure_cdev_add:
	for( j = i; j &gt;= 0; j-- ) {
		device_destroy( dev_class, MKDEV( chardevicedriver_major, ( chardevicedriver_minor + j ) ) );
		cdev_del( &amp;(chardevicedriver_cdevp[ j ].cdev) );
	}
	class_destroy( dev_class );
failure_create_class:
	kfree( chardevicedriver_cdevp );
failure_alloc_cdev:
	unregister_chrdev_region( dev, CHARDEVICEDRIVER_COUNT );
failure_register_chrdev:
	return ret;
}

// clean up module function
static void __exit chardevicedriver_exit(void)
{
	int i = 0;

	printk(KERN_ALERT "CharDeviceDriver: Entry chardevicedriver_exit !\n");

	// destroy device and delete cdev object
	for( i = 0; i &lt; CHARDEVICEDRIVER_COUNT; i++ ) {
		device_destroy( dev_class, MKDEV( chardevicedriver_major, ( chardevicedriver_minor + i ) ) );
		cdev_del( &amp;( chardevicedriver_cdevp[ i ].cdev ) );
	}

	// destroy device class;
	class_destroy( dev_class );

	// free memory for private struct
	kfree( chardevicedriver_cdevp );
	chardevicedriver_cdevp = NULL;

	// unregister device number
	unregister_chrdev_region( MKDEV( chardevicedriver_major, chardevicedriver_minor ), CHARDEVICEDRIVER_COUNT );
gpio_free(S5PV210_GPH0(0));
 gpio_free(S5PV210_GPH0(1));
 gpio_free(S5PV210_GPC1(3));
gpio_free(S5PV210_GPC1(4));
 printk(KERN_ALERT "CharDeviceDriver: Exit chardevicedriver_exit !\n");

}

// the declarations of initialization and cleaning up module functions
module_init(chardevicedriver_init);
module_exit(chardevicedriver_exit);

// module information
MODULE_AUTHOR("Tarena");
MODULE_DESCRIPTION("My first char device driver to add device file operations");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("CharDeviceDriver");
</pre><div class="sh_sourceCode snippet-hide"><pre><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-revealed snippet-toggle sh_url">隐藏</a></pre></div></div><div class="snippet-reveal sh_acid snippet-wrap" style=""><pre class="sh_sourceCode"><a href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" class="snippet-toggle sh_url">代码</a></pre></div></div>
    <p class="number">2.编写testchardevicedriver1.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>testchardevicedriver1<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   testchardevicedriver1.c
</pre></div></div>
    <p>testchardevicedriver1.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>stdio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>stdlib<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>fcntl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>sys<span class="sh_symbol">/</span>ioctl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> fd<span class="sh_symbol">;</span></li><li><span class="sh_type">char</span> ch<span class="sh_symbol">;</span></li><li>unsigned <span class="sh_type">char</span> buf<span class="sh_symbol">=</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">(</span><span class="sh_type">int</span> argc<span class="sh_symbol">,</span> <span class="sh_type">char</span> <span class="sh_symbol">**</span>argv<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;unsigned <span class="sh_type">char</span> key_value <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>        <span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>        &nbsp;&nbsp;&nbsp;&nbsp;</li><li>        fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver0"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp; <span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Failure to open device file: /dev/chardevicedriver0!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">exit</span><span class="sh_symbol">(</span> <span class="sh_symbol">-</span><span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to open device file: /dev/chardevicedriver0!</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">while</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">((</span><span class="sh_function">read</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>key_value<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>key_value<span class="sh_symbol">)))==</span><span class="sh_number">1</span><span class="sh_symbol">)</span></li><li>         <span class="sh_cbracket">{</span> </li><li>             buf <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>             <span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"key value = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> key_value<span class="sh_symbol">);</span></li><li>             <span class="sh_function">write</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>buf<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>      <span class="sh_keyword">else</span></li><li>         <span class="sh_cbracket">{</span> </li><li>             buf <span class="sh_symbol">=</span> <span class="sh_number">1</span><span class="sh_symbol">;</span> </li><li>             <span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"key value = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> key_value<span class="sh_symbol">);</span></li><li>             <span class="sh_function">write</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>buf<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>        <span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">close</span><span class="sh_symbol">(</span> fd <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to test device: /dev/chardevicedriver !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;

#include &lt;sys/ioctl.h&gt;


int fd;
char ch;
unsigned char buf=1;

int main(int argc, char **argv)
{
	unsigned char key_value = 0;
        int ret = 0;
        	
        fd = open( "/dev/chardevicedriver0", O_RDWR );
	 if( 0 &gt; fd ) {
		printf("Failure to open device file: /dev/chardevicedriver0!\n");
		exit( -1 );
	}
	printf("Success to open device file: /dev/chardevicedriver0!\n");


	while( 1 ) {
		if((read(fd, &amp;key_value, sizeof(key_value)))==1)
         { 
             buf = 0;
             printf("key value = %d\n", key_value);
             write(fd, &amp;buf, sizeof(buf));
	}
      else
         { 
             buf = 1; 
             printf("key value = %d\n", key_value);
             write(fd, &amp;buf, sizeof(buf));
	}
        }
	close( fd );
	printf("Success to test device: /dev/chardevicedriver !\n");

	return 0;

}
</pre></div></div>
    <p class="number">3.编写testchardevicedriver2.c源文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ <span class="sh_usertype">vi</span><span class="sh_normal">   </span>testchardevicedriver2<span class="sh_symbol">.</span>c</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ vi   testchardevicedriver2.c
</pre></div></div>
    <p>testchardevicedriver2.c源代码如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>#include <span class="sh_symbol">&lt;</span>stdio<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>stdlib<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li>#include <span class="sh_symbol">&lt;</span>fcntl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li>#include <span class="sh_symbol">&lt;</span>sys<span class="sh_symbol">/</span>ioctl<span class="sh_symbol">.</span>h<span class="sh_symbol">&gt;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> fd<span class="sh_symbol">;</span></li><li><span class="sh_type">char</span> ch<span class="sh_symbol">;</span></li><li>unsigned <span class="sh_type">char</span> buf<span class="sh_symbol">=</span><span class="sh_number">1</span><span class="sh_symbol">;</span></li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_type">int</span> <span class="sh_function">main</span><span class="sh_symbol">(</span><span class="sh_type">int</span> argc<span class="sh_symbol">,</span> <span class="sh_type">char</span> <span class="sh_symbol">**</span>argv<span class="sh_symbol">)</span></li><li><span class="sh_cbracket">{</span></li><li>       unsigned <span class="sh_type">char</span> key_value <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>       <span class="sh_type">int</span> ret <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;</li><li>       fd <span class="sh_symbol">=</span> <span class="sh_function">open</span><span class="sh_symbol">(</span> <span class="sh_string">"/dev/chardevicedriver1"</span><span class="sh_symbol">,</span> O_RDWR <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">(</span> <span class="sh_number">0</span> <span class="sh_symbol">&gt;</span> fd <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Failure to open device file: /dev/chardevicedriver1 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">exit</span><span class="sh_symbol">(</span> <span class="sh_symbol">-</span><span class="sh_number">1</span> <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to open device file: /dev/chardevicedriver1 !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">while</span><span class="sh_symbol">(</span> <span class="sh_number">1</span> <span class="sh_symbol">)</span> <span class="sh_cbracket">{</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">if</span><span class="sh_symbol">((</span><span class="sh_function">read</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>key_value<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>key_value<span class="sh_symbol">)))==</span><span class="sh_number">1</span><span class="sh_symbol">)</span></li><li>                  <span class="sh_cbracket">{</span> </li><li>                buf <span class="sh_symbol">=</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li>                <span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"key value = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> key_value<span class="sh_symbol">);</span></li><li>                <span class="sh_function">write</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>buf<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>              <span class="sh_comment">//if((read(fd, &amp;key_value, sizeof(key_value)))==1)</span></li><li>                <span class="sh_keyword">else</span></li><li>                <span class="sh_cbracket">{</span> </li><li>              </li><li>         buf <span class="sh_symbol">=</span> <span class="sh_number">1</span><span class="sh_symbol">;</span> </li><li>         <span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"key value = %d</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">,</span> key_value<span class="sh_symbol">);</span></li><li>          <span class="sh_function">write</span><span class="sh_symbol">(</span>fd<span class="sh_symbol">,</span> <span class="sh_symbol">&amp;</span>buf<span class="sh_symbol">,</span> <span class="sh_function">sizeof</span><span class="sh_symbol">(</span>buf<span class="sh_symbol">));</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_cbracket">}</span></li><li>        <span class="sh_cbracket">}</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">close</span><span class="sh_symbol">(</span> fd <span class="sh_symbol">);</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_function">printf</span><span class="sh_symbol">(</span><span class="sh_string">"Success to test device: /dev/chardevicedriver !</span><span class="sh_specialchar">\n</span><span class="sh_string">"</span><span class="sh_symbol">);</span></li><li><span style="display:none;">&nbsp;</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_keyword">return</span> <span class="sh_number">0</span><span class="sh_symbol">;</span></li><li><span class="sh_cbracket">}</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;fcntl.h&gt;

#include &lt;sys/ioctl.h&gt;



int fd;
char ch;
unsigned char buf=1;

int main(int argc, char **argv)
{
       unsigned char key_value = 0;
       int ret = 0;
	
       fd = open( "/dev/chardevicedriver1", O_RDWR );
	if( 0 &gt; fd ) {
		printf("Failure to open device file: /dev/chardevicedriver1 !\n");
		exit( -1 );
	}
	printf("Success to open device file: /dev/chardevicedriver1 !\n");

		while( 1 ) {
		if((read(fd, &amp;key_value, sizeof(key_value)))==1)
                  { 
                buf = 0;
                printf("key value = %d\n", key_value);
                write(fd, &amp;buf, sizeof(buf));
	}
              //if((read(fd, &amp;key_value, sizeof(key_value)))==1)
                else
                { 
              
         buf = 1; 
         printf("key value = %d\n", key_value);
          write(fd, &amp;buf, sizeof(buf));
	}
        }
	close( fd );
	printf("Success to test device: /dev/chardevicedriver !\n");

	return 0;
}
</pre></div></div>
    <p class="number">4.编写Makefile文件。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li># makefile <span class="sh_keyword">for</span> kernel module</li><li><span style="display:none;">&nbsp;</span></li><li>MODNAME <span class="sh_symbol">=</span> chardevicedriver</li><li>CROSS_COMPILE <span class="sh_symbol">=</span> arm<span class="sh_symbol">-</span>linux<span class="sh_symbol">-</span></li><li>TESTPRE&nbsp;&nbsp;&nbsp;&nbsp;<span class="sh_symbol">=</span> test</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_function">ifeq</span> <span class="sh_symbol">(</span>$<span class="sh_symbol">(</span>PLATFORM<span class="sh_symbol">),</span> PC<span class="sh_symbol">)</span></li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>lib<span class="sh_symbol">/</span>modules<span class="sh_symbol">/</span>$<span class="sh_symbol">(</span><span class="sh_usertype">shell</span><span class="sh_normal"> </span>uname <span class="sh_symbol">-</span>r<span class="sh_symbol">)/</span>build</li><li><span class="sh_keyword">else</span></li><li>CC <span class="sh_symbol">=</span> $<span class="sh_symbol">(</span>CROSS_COMPILE<span class="sh_symbol">)</span>gcc</li><li>KERNELDIR <span class="sh_symbol">?=</span> <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>tools<span class="sh_symbol">/</span>linux<span class="sh_number">-2.6.35.7</span></li><li>endif</li><li><span style="display:none;">&nbsp;</span></li><li>obj<span class="sh_symbol">-</span>m <span class="sh_symbol">:=</span> $<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).</span>o</li><li><span style="display:none;">&nbsp;</span></li><li><span class="sh_keyword">default</span><span class="sh_symbol">:</span> test driver</li><li><span style="display:none;">&nbsp;</span></li><li>test<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>CC<span class="sh_symbol">)</span> $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">1</span><span class="sh_symbol">.</span>c <span class="sh_symbol">-</span>o $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">1</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>CC<span class="sh_symbol">)</span> $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">2</span><span class="sh_symbol">.</span>c <span class="sh_symbol">-</span>o $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">2</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>driver<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Compiling device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;$<span class="sh_symbol">(</span>MAKE<span class="sh_symbol">)</span> <span class="sh_symbol">-</span>C $<span class="sh_symbol">(</span>KERNELDIR<span class="sh_symbol">)</span> M<span class="sh_symbol">=</span>$<span class="sh_symbol">(</span>PWD<span class="sh_symbol">)</span> modules</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li><span style="display:none;">&nbsp;</span></li><li>clean<span class="sh_symbol">:</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup test program..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>f $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">1</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>f $<span class="sh_symbol">(</span>TESTPRE<span class="sh_symbol">)</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">)</span><span class="sh_number">2</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo <span class="sh_string">"Cleanup device driver..."</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@rm <span class="sh_symbol">-</span>rf <span class="sh_symbol">*.</span>o <span class="sh_symbol">*.</span>ko <span class="sh_symbol">*.</span>mod<span class="sh_symbol">.*</span> <span class="sh_symbol">.</span>$<span class="sh_symbol">(</span>MODNAME<span class="sh_symbol">).*</span> <span class="sh_symbol">.</span>tmp<span class="sh_symbol">*</span> module<span class="sh_symbol">*</span> Module<span class="sh_symbol">*</span></li><li>&nbsp;&nbsp;&nbsp;&nbsp;@echo</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;"># makefile for kernel module

MODNAME = chardevicedriver
CROSS_COMPILE = arm-linux-
TESTPRE	= test

ifeq ($(PLATFORM), PC)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
else
CC = $(CROSS_COMPILE)gcc
KERNELDIR ?= /home/tarena/workdir/tools/linux-2.6.35.7
endif

obj-m := $(MODNAME).o

default: test driver

test:
	@echo "Compiling test program..."
	$(CC) $(TESTPRE)$(MODNAME)1.c -o $(TESTPRE)$(MODNAME)1
	$(CC) $(TESTPRE)$(MODNAME)2.c -o $(TESTPRE)$(MODNAME)2
	@echo

driver:
	@echo "Compiling device driver..."
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@echo

clean:
	@echo "Cleanup test program..."
	@rm -f $(TESTPRE)$(MODNAME)1
	@rm -f $(TESTPRE)$(MODNAME)2
	@echo
	@echo "Cleanup device driver..."
	@rm -rf *.o *.ko *.mod.* .$(MODNAME).* .tmp* module* Module*
	@echo
</pre></div></div>
    <p class="number">5.编译chardevicedriver驱动模块，并将生成的chardevicedriver.ko、testchardevicedriver1、testchardevicedriver2文件拷贝到指定目录下，执行如下命令。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li>$ make </li><li>$ <span class="sh_usertype">cp</span><span class="sh_normal">  </span>chardevicedriver<span class="sh_symbol">.</span>ko  <span class="sh_usertype">testchardevicedriver1</span><span class="sh_normal"> </span>testchardevicedriver2   <span class="sh_symbol">/</span>home<span class="sh_symbol">/</span>tarena<span class="sh_symbol">/</span>workdir<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span>rootfs<span class="sh_symbol">/</span></li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">$ make 
$ cp  chardevicedriver.ko  testchardevicedriver1 testchardevicedriver2   /home/tarena/workdir/rootfs/rootfs/
</pre></div></div>
    <p class="number">6.重新启动TPAD，动态加载该驱动模块，运行测试。</p>
    <p>在TPAD上，使用insmod命令和rmmod命令加载并卸载chardevicedriver.ko驱动。命令如下：</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_usertype">insmod</span><span class="sh_normal">   </span>chardevicedriver<span class="sh_symbol">.</span>ko</li><li><span class="sh_symbol">/</span>#  ls   <span class="sh_symbol">/</span>dev<span class="sh_symbol">/</span>   <span class="sh_symbol">-</span>l</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  insmod   chardevicedriver.ko
/#  ls   /dev/   -l
</pre></div></div>
    <p>运行加载驱动的命令之后，查看TPAD的/dev目录，程序已经自动在该目录下创建设备文件chardevicedriver0和chardevicedriver1两个设备文件，如图-17所示。</p>
    <div class="image">
      <img src="image017.png">
      <p>图-17</p>
    </div>
    <p class="number">7.分别运行两个应用测试程序，测试驱动程序。</p>
    <div class="snippet-container" style="undefined;"><div class="sh_acid snippet-wrap"><div class="snippet-menu sh_sourceCode" style="display:none;"><pre style="display: none; "><a class="snippet-copy sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#" style="display: none; ">copy</a><a class="snippet-text sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">text</a><a class="snippet-window sh_url" href="http://pdf5.tarena.com.cn/tts6materials/TTS6/EMBED/ESD_V01/DRIVER/DAY02/CASE/01/index.html?bd4fe097-b98d-4784-be2a-9289d8564fa7#">pop-up</a></pre></div><pre class="code sh_java snippet-formatted sh_sourceCode"><ol class="snippet-num"><li><span class="sh_symbol">/</span>#  <span class="sh_symbol">./</span> testchardevicedriver1</li><li><span class="sh_symbol">/</span>#  <span class="sh_symbol">./</span> testchardevicedriver2</li></ol></pre><pre class="snippet-textonly sh_sourceCode" style="display:none;">/#  ./ testchardevicedriver1
/#  ./ testchardevicedriver2
</pre></div></div>
    <p>测试程序运行过程中，按住TPAD上的KEY1UP键，则LED1灯亮，抬起则灯灭。按住TPAD上的KEY2DOWN键，则LED2灯亮，抬起则灯灭。</p>
    <h3>6.4 扩展</h3>
  
</body></html>
</body></html>