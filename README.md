# bullet_debug_drawer

由于bullet的 debug drawer 并没有实现，而在example 中实现的 debug drawer过于复杂并且在linux上兼容性不好，因此用opengl实现了一个简单的 debug drawer



## dependencies 

sudo apt-get install libbullet-dev
sudo apt-get install freeglut3-dev
sudo apt-get install libgl1-mesa-dev

## running

cd /path/to/this/project/
cmake .
make 
