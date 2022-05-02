# cmake-template

#### 介绍
一个CMake Project的模板仓库.


本文将会介绍如何书写一个完备的CMakeLists.txt文件，满足一般项目的基础构建要求，CMake的语法将会更多介绍项目配置命令，主要有以下内容：

设置一些自定义编译控制开关和自定义编译变量控制编译过程
根据不同编译类型配置不同的编译选项和链接选项
添加头文件路径、编译宏等常规操作
编译生成不同类型的目标文件，包括可执行文件、静态链接库和动态链接库
安装、打包和测试


一 基础配置
下面先介绍一些CMake项目通常都需要进行的配置。下面介绍的内容以make作为构建工具作为示例。

下面的示例代码可以在开源项目``` cmake-template``` 中查看（当前``` commit id：c7c6b15``` ）。 把仓库克隆下来结合源码阅读本文效果更佳，如果有帮助，请点下Star哟。

1 设置项目版本和生成version.h
一般来说，项目一般需要设置一个版本号，方便进行版本的发布，也可以根据版本对问题或者特性进行追溯和记录。

通过project命令配置项目信息，如下：
``` 
project(CMakeTemplate VERSION 1.0.0 LANGUAGES C CXX)
``` 
第一个字段是项目名称；通过``` VERSION``` 指定版本号，格式为```main.minor.patch.tweak``` ，并且CMake会将对应的值分别赋值给以下变量（如果没有设置，则为空字符串）：
```cpp 
PROJECT_VERSION, <PROJECT-NAME>_VERSION
PROJECT_VERSION_MAJOR, <PROJECT-NAME>_VERSION_MAJOR
PROJECT_VERSION_MINOR, <PROJECT-NAME>_VERSION_MINOR
PROJECT_VERSION_PATCH, <PROJECT-NAME>_VERSION_PATCH
PROJECT_VERSION_TWEAK, <PROJECT-NAME>_VERSION_TWEAKS
``` 

因此，结合前一篇文章提到的configure_file命令，可以配置自动生成版本头文件，将头文件版本号定义成对应的宏，或者定义成接口，方便在代码运行的时候了解当前的版本号。

比如:

```cpp 
configure_file(src/c/cmake_template_version.h.in "${PROJECT_SOURCE_DIR}/src/c/cmake_template_version.h")
``` 

假如cmake_template_version.h.in内容如下：

```cpp 
#define CMAKE_TEMPLATE_VERSION_MAJOR @CMakeTemplate_VERSION_MAJOR@
#define CMAKE_TEMPLATE_VERSION_MINOR @CMakeTemplate_VERSION_MINOR@
#define CMAKE_TEMPLATE_VERSION_PATCH @CMakeTemplate_VERSION_PATCH@
``` 

执行cmake配置构建系统后，将会自动生成文件：cmake_template_version.h，其中``` @<var-name>@``` 将会被替换为对应的值：

```cpp 
#define CMAKE_TEMPLATE_VERSION_MAJOR 1
#define CMAKE_TEMPLATE_VERSION_MINOR 0
#define CMAKE_TEMPLATE_VERSION_PATCH 0
``` 

2 指定编程语言版本
为了在不同机器上编译更加统一，最好指定语言的版本，比如声明C使用c99标准，C++使用c++17标准：
``` 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
``` 
这里设置的变量都是CMAKE_开头(包括project命令自动设置的变量)，这类变量都是CMake的内置变量，正是通过修改这些变量的值来配置CMake构建的行为。

CMAKE_、_CMAKE或者以下划线开头后面加上任意CMake命令的变量名都是CMake保留的。
3 配置编译选项
通过命令```add_compile_options```命令可以为所有编译器配置编译选项（同时对多个编译器生效）； 通过设置变量```CMAKE_C_FLAGS```可以配置c编译器的编译选项； 而设置变量```CMAKE_CXX_FLAGS```可配置针对c++编译器的编译选项。 比如：
```cpp 
add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")
``` 

4 配置编译类型
通过设置变量```CMAKE_BUILD_TYPE```来配置编译类型，可设置为：```Debug、Release、RelWithDebInfo、MinSizeRel```等，比如：
```cpp 
set(CMAKE_BUILD_TYPE Debug)
``` 

当然，更好的方式应该是在执行cmake命令的时候通过参数-D指定：
``` 
cmake -B build -DCMAKE_BUILD_TYPE=Debug
``` 
如果设置编译类型为Debug，那么对于c编译器，CMake会检查是否有针对此编译类型的编译选项CMAKE_C_FLAGS_DEBUG，如果有，则将它的配置内容加到CMAKE_C_FLAGS中。

可以针对不同的编译类型设置不同的编译选项，比如对于Debug版本，开启调试信息，不进行代码优化：
```cpp
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
``` 
对于Release版本，不包含调试信息，优化等级设置为2：
```cpp
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
``` 

5 添加全局宏定义
通过命令```add_definitions```可以添加全局的宏定义，在源码中就可以通过判断不同的宏定义实现相应的代码逻辑。用法如下：

```cpp
add_definitions(-DDEBUG -DREAL_COOL_ENGINEER)
``` 


6 添加include目录
通过命令```include_directories```来设置头文件的搜索目录，比如：

```cpp
include_directories(src/c)
```


二 编译目标文件
一般来说，编译目标(target)的类型一般有静态库、动态库和可执行文件。 这时编写CMakeLists.txt主要包括两步：

编译：确定编译目标所需要的源文件
链接：确定链接的时候需要依赖的额外的库
下面以开源项目(cmake-template)来演示。项目的目录结构如下：
```cpp 
./cmake-template
├── CMakeLists.txt
├── src
│   └── c
│       ├── cmake_template_version.h
│       ├── cmake_template_version.h.in
│       ├── main.c
│       └── math
│           ├── add.c
│           ├── add.h
│           ├── minus.c
│           └── minus.h
└── test
    └── c
        ├── test_add.c
        └── test_minus.
``` 

项目的构建任务为：

将math目录编译成静态库，命名为math
编译main.c为可执行文件demo，依赖math静态库
编译test目录下的测试程序，可以通过命令执行所有的测试
支持通过命令将编译产物安装及打包
1 编译静态库
这一步需要将项目目录路径src/c/math下的源文件编译为静态库，那么需要获取编译此静态库需要的文件列表，可以使用set命令，或者file命令来进行设置。比如：

```cpp
file(GLOB_RECURSE MATH_LIB_SRC src/c/math/*.c)
add_library(math STATIC ${MATH_LIB_SRC})
```

使用file命令获取src/c/math目录下所有的*.c文件，然后通过```add_library```命令编译名为math的静态库，库的类型是第二个参数```STATIC```指定的。

如果指定为```SHARED```则编译的就是动态链接库。


2 编译可执行文件
通过```add_executable```命令来往构建系统中添加一个可执行构建目标，同样需要指定编译需要的源文件。但是对于可执行文件来说，有时候还会依赖其他的库，则需要使用```target_link_libraries```命令来声明构建此可执行文件需要链接的库。

在示例项目中，main.c就使用了```src/c/math```下实现的一些函数接口，所以依赖于前面构建的math库。所以在CMakeLists.txt中添加以下内容：
```cpp
add_executable(demo src/c/main.c)
target_link_libraries(demo math)
```

第一行说明编译可执行文件demo需要的源文件（可以指定多个源文件，此处只是以单个文件作为示例）；第二行表明对math库存在依赖。

此时可以在项目的根目录下执行构建和编译命令，并执行demo:
```cpp
➜ # cmake -B cmake-build
➜ # cmake --build cmake-build
➜ # ./cmake-build/demo
Hello CMake!
10 + 24 = 34
40 - 96 = -56
```

三 安装和打包
1 安装
对于安装来说，其实就是要指定当前项目在执行安装时，需要安装什么内容:

通过```install```命令来说明需要安装的内容及目标路径；
通过设置```CMAKE_INSTALL_PREFIX```变量说明安装的路径；
3.15往后的版本可以使用```cmake --install --prefix <install-path>```覆盖指定安装路径。
比如，在示例项目中，把math和demo两个目标按文件类型安装：
```cpp
install(TARGETS math demo
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
```

这里通过```TARGETS```参数指定需要安装的目标列表；参数```RUNTIME DESTINATION、LIBRARY DESTINATION、ARCHIVE DESTINATION```分别指定可执行文件、库文件、归档文件分别应该安装到安装目录下个哪个子目录。

如果指定```CMAKE_INSTALL_PREFIX```为```/usr/local```，那么math库将会被安装到路径```/usr/local/lib/```目录下；而demo可执行文件则在```/usr/local/bin```目录下。

```CMAKE_INSTALL_PREFIX```在不同的系统上有不同的默认值，使用的时候最好显式指定路径。
同时，还可以使用install命令安装头文件：

```cpp
file(GLOB_RECURSE MATH_LIB_HEADERS src/c/math/*.h)
install(FILES ${MATH_LIB_HEADERS} DESTINATION include/math)
```

假如将安装到当前项目的output文件夹下，可以执行：
```cpp
> ➜ # cmake -B cmake-build -DCMAKE_INSTALL_PREFIX=./output
> ➜ # cmake --build cmake-build
> ➜ # cd cmake-build && make install && cd -
> Install the project...
-- Install configuration: ""
-- Installing: .../cmake-template/output/lib/libmath.a
-- Installing: .../gitee/cmake-template/output/bin/demo
-- Installing: .../gitee/cmake-template/output/include/math/add.h
-- Installing: .../gitee/cmake-template/output/include/math/minus.h 
```

可以看到安装了前面install命令指定要安装的文件，并且不同类型的目标文件安装到不同子目录。

2 打包
要使用打包功能，需要执行include(CPack)启用相关的功能，在执行构建编译之后使用cpack命令行工具进行打包安装；对于make工具，也可以使用命令make package。

打包的内容就是install命令安装的内容，关键需要设置的变量有：

```cpp
CPACK_GENERATOR	             打包使用的压缩工具，比如"ZIP"
CPACK_OUTPUT_FILE_PREFIX	 打包安装的路径前缀
CPACK_INSTALL_PREFIX	     打包压缩包的内部目录前缀
CPACK_PACKAGE_FILE_NAME	     打包压缩包的名称，由CPACK_PACKAGE_NAME、CPACK_PACKAGE_VERSION、CPACK_SYSTEM_NAME三部分构成
```

比如：
```cpp
include(CPack)
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "CMakeTemplate")
set(CPACK_SET_DESTDIR ON)
set(CPACK_INSTALL_PREFIX "")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
```

假如```CPACK_OUTPUT_FILE_PREFIX```设置为```/usr/local/package```； ```CPACK_INSTALL_PREFIX```设置为```real/cool/engineer```； ```CPACK_PACKAGE_FILE_NAME```
设置为```CMakeTemplate-1.0.0； ```

那么执行打包文件的生成路径为：
```/usr/local/package/CMakeTemplate-1.0.0.zip```


解压这个包得到的目标文件则会位于路径下：```/usr/local/package/real/cool/engineer/```


此时重新执行构建，使用cpack命令执行打包：
```cpp
➜ # cmake -B cmake-build -DCPACK_OUTPUT_FILE_PREFIX=`pwd`/output
➜ # cmake --build cmake-build
➜ # cd cmake-build && cpack && cd -
CPack: Create package using ZIP
CPack: Install projects
CPack: - Run preinstall target for: CMakeTemplate
CPack: - Install project: CMakeTemplate
CPack: Create package
CPack: - package: /Users/Farmer/gitee/cmake-template/output/CMakeTemplate-1.0.0-Darwin.zip generated.
```

cpack有一些参数是可以覆盖CMakeLists.txt设置的参数的，比如这里的-G参数就会覆盖变量CPACK_GENERATOR，具体细节可使用cpack --help查看。

四 测试
CMake的测试功能使用起来有几个步骤：

CMakeLists.txt中通过命令```enable_testing()```或者```include(CTest)```来启用测试功能；
使用```add_test```命令添加测试样例，指定测试的名称和测试命令、参数；
构建编译完成后使用```ctest```命令行工具运行测试。
为了控制是否开启测试，可使用option命令设置一个开关，在开关打开时才进行测试，比如：
```cpp
option(CMAKE_TEMPLATE_ENABLE_TEST "Whether to enable unit tests" ON)
if (CMAKE_TEMPLATE_ENABLE_TEST)
    message(STATUS "Unit tests enabled")
    enable_testing()
endif()
```

这里为了方便后续演示，暂时是默认开启的。


1 编写测试程序
在此文的示例代码中，针对add.c和minus.c实现了两个测试程序，它们的功能是类似的，接受三个参数，用第一和第二个计算两个参数的和或者差，判断是否和第三个参数相等，如test_add.c的代码为：

```cpp
// @Author: Farmer Li, 公众号: 很酷的程序员/RealCoolEngineer
// @Date: 2021-05-10

#include <stdio.h>
> #include <stdlib.h>

> #include "math/add.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Usage: test_add v1 v2 expected\n");
    return 1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  int expected = atoi(argv[3]);
  int res = add_int(x, y);

  if (res != expected) {
    return 1;
  } else {
    return 0;
  }
}
``` 


这里需要注意的是，对于测试程序来说，如果返回值非零，则表示测试失败。

2 添加测试
接下来先使用add_executable命令生成测试程序，然后使用add_test命令添加单元测试：
```cpp
add_executable(test_add test/c/test_add.c)
add_executable(test_minus test/c/test_minus.c)
target_link_libraries(test_add math)
target_link_libraries(test_minus math)
add_test(NAME test_add COMMAND test_add 10 24 34)
add_test(NAME test_minus COMMAND test_minus 40 96 -56)
``` 

3 执行测试
现在重新执行cmake命令更新构建系统，执行构建，再执行测试：
```cpp
➜ # cmake -B cmake-build
➜ # cmake --build cmake-build
➜ # cd cmake-build && ctest && cd -
Test project /Users/Farmer/gitee/cmake-template/cmake-build
    Start 1: test_add
1/2 Test #1: test_add .........................   Passed    0.00 sec
    Start 2: test_minus
2/2 Test #2: test_minus .......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2
``` 

使用```ctest -VV```则可以看到更加详细的测试流程和结果。

在CMake 3.20往后的版本中，ctest可以使用```--test-dir```指定测试执行目录。
至此，一个较为完备的CMakeLists.txt就开发完成了。
