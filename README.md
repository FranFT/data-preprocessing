# Data Preprocessing
This module is able to split an image data base into Training and Test sets. Furthermore it is thought to perform data augmentation technique in some cases using [OpenCV](http://opencv.org/).

### Supported data-bases and requirements
- [Yalefaces](http://cvc.cs.yale.edu/cvc/projects/yalefaces/yalefaces.html): Images need to be transform from .gif to .png.
- [KDEF](http://www.emotionlab.se/resources/kdef): In development.

### Instructions
Unzip database in /res directory. For example:
- res/yalefaces/
- res/KDEF/
- ...

Then compile and execute using the following commands:
```sh
$ mkdir build
$ cd build
$ cmake .. & make
```

[//]: <> (http://dillinger.io/)
