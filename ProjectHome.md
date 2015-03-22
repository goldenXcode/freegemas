![http://freegemas.googlecode.com/svn/web/freegemas_header.png](http://freegemas.googlecode.com/svn/web/freegemas_header.png)

![http://freegemas.googlecode.com/svn/web/gemas_showcase.png](http://freegemas.googlecode.com/svn/web/gemas_showcase.png)

**Freegemas** is an open source version of the well known Bejeweled, for GNU/Linux and Windows. It's written in C++ and it uses [Gosu](http://www.libgosu.org) as the graphic API.

# NEWS #
**Freegemas is now part of Guadalinex**, a Ubuntu-based operating system promoted by the government of Andalusia (Spain) used in schools, and other public spaces. If you happen to use Guadalinex, you can install Freegemas using
```
sudo apt-get install freegemas
```

Amazing! Special thanks go to [Álvaro Pinel](http://about.me/alvaropinel) and [Alfonso De Cala](http://www.linkedin.com/in/alfonsodecala) for their quick response and support building the package.

## Windows users ##
There are packaged [downloads](https://code.google.com/p/freegemas/downloads/list) for Windows, so no compilation is needed.

## Dependencies ##
Freegemas shares the sames dependencies as Gosu. You will need the following packages (install via sudo apt-get install `<packagename`>):
  * g++
  * libgl1-mesa-dev
  * libpango1.0-dev
  * libboost-dev (>= 1.36.0—please check the version you have!)
  * libsdl-mixer1.2-dev
  * libsdl-ttf2.0-dev

Copy-and-pastable command line for Ubuntu, last tested 2010, should work across all versions:

```
sudo apt-get install g++ libgl1-mesa-dev libpango1.0-dev libboost-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libopenal-dev libsndfile1-dev libfreeimage-dev
```

## Checking out and compiling ##
Use this command to anonymously check out the latest project source code:
```
svn checkout http://freegemas.googlecode.com/svn/trunk/ freegemas-read-only 
```

Then, use the following to compile the graphic library
```
make libgosu
```

Finally, compile and run the project using
```
make
./programa
```

## Gameplay video ##
<a href='http://www.youtube.com/watch?feature=player_embedded&v=DonQd48B9AU' target='_blank'><img src='http://img.youtube.com/vi/DonQd48B9AU/0.jpg' width='425' height=344 /></a>