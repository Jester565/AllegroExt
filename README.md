# AllegroExt
AllegroExt takes the lower level Allegro library and creates componenets found in Java's LibGDX library including an FPS logger, images, input managment, music, screen text, shape renderers, and text fields.  To get a display up and running with these components simply inherit from Core like so:
```
#include "ExampleCore.h"

ExampleCore::ExampleCore(const std::string& resourcePath)
	:AllegroExt::Core(resourcePath)
{ }

bool ExampleCore::init()
{
	if (Core::init())
	{
            //Initialize assets here  
            return true;
	}
	return false;
}

void ExampleCore::draw()
{
	//Draw game here
}
```

## Installation
Requirements: Allegro (5.2.4)

#### Requirement Installation
1. Installing Allegro
    * Windows:
        1. After you generate the FarmerGame solution, goto Tools -> NuGet Packet Manager -> Manage NuGet Packages for Solution... -> Browse
        2. Search for and install Allegro on AllegroExt
        3. Goto the properties for the Allegro projects and set the dependencies like this ![Allegro Configuration](https://github.com/Jester565/FarmerGame/blob/master/rdme/AllegConf.png)
    * Ubuntu:
        1. Install Allegro5 Package with [this guide](https://wiki.allegro.cc/index.php?title=Install_Allegro_from_Ubuntu_PPAs)

#### Build
```
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017" -A x64 -T host=x64        #For Ubuntu don't include -G option
```
Run make or build the solution  

# Examples
I'll add some simple examples soon.  For now you can see the library used in [FarmerGame](https://github.com/Jester565/FarmerGame), [Tropadom2](https://github.com/Jester565/Tropadom2), [TropadomServer](https://github.com/Jester565/Tropadom2Server), or the [Lighting4 Example](https://github.com/Jester565/Lighting4/tree/master/examples/example1).
