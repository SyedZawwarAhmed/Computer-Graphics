#include<string>
#include<iostream>
#include<fstream>
#include<glut.h>
using namespace std;
struct RGB{
	unsigned char r,g,b;
	};
class RGBpixmap{

private:
	int nRows,nCols;
	RGB	*pixel;
public:
	RGBpixmap(){
		nRows=nCols=0;
		pixel=0;
}
	RGBpixmap(int r,int c)
	{
		nRows=r;
		nCols=c;
		pixel=new RGB[r*c];
	}
void setPixel (int x,int y,RGB color)
{
if(x>=0&&x<nCols&&y>=0&&y<nRows)
pixel[nCols*y+x]=color;
}
RGB getPixel(int x,int y)
{
return pixel[nCols*y+x];
}
void Draw()
{
	glDrawPixels(nCols,nRows,GL_RGB,GL_UNSIGNED_BYTE,pixel);
}
void read( int x,int y,int wid,int ht){
nRows=ht;
nCols=wid;
pixel= new RGB[nRows*nCols];
if(!pixel)
exit(-1);
glReadPixels(x,y,nCols,nRows,GL_RGB,GL_UNSIGNED_BYTE,pixel);
}
void copy (int x, int y,int wid,int ht)
{
	glCopyPixels(x,y,wid,ht,GL_COLOR);
	int readBmpFile(char *fname);
	int writeBmpFile(char *fname);
}
int readBMPFile(char *fname)
{
	fstream instream(fname,ios::in | ios::binary);	
	if(!instream)
	{
		std::cout<<"FILE CANT  BE OPEN";
		exit(0);
	}

	char ch[2];
	unsigned offset;
	unsigned width,height;
	instream.seekp(0,ios::cur);
	instream.read((char *)&ch[0],sizeof(unsigned char));///B
	std::cout << (char)ch[0];
	instream.read((char *)&ch[1],sizeof(unsigned char));///M
	std::cout << (char)ch[1];
	instream.seekp(8,ios::cur);//set postion to bitmap offset address
	instream.read((char*)&offset,4); //reading it in 4 byte variable offset

	std::cout << "offset= "<<(int)offset; ///start location of actual data of picture
	instream.seekp(4,ios::cur);
	instream.read((char*)&width,4); //width of pic
	instream.read((char*)&height,4);//height of pic
	std::cout << "w="<<(int)width;
	std::cout << "h="<<(int)height;
	/*
	std::cout <<"size of unsign"<<sizeof(unsigned short);
	instream.seekp(8,ios::cur);
	instream.read((char*)&nCols,4); 
	instream.read((char*)&nRows,4);
	std::cout << "col="<<(int)nRows;
	*/
	instream.seekp((int)offset,ios::beg);
	nRows=height;
	nCols=width;
	RGB color;
	pixel=new RGB[nRows*nCols];
	for(unsigned int y=0;y<height;y++)
	{
		for(unsigned int x=0;x<width;x++)
		{
			//color rgb are present in form of bgr reverse order 
		instream.read((char*)&color.b,1);
		instream.read((char*)&color.g,1);
		instream.read((char*)&color.r,1);
		setPixel(x,y,color);
			
		}

	}
return(1);
}
void writeBmpFile(char *fname)
{



}
};
