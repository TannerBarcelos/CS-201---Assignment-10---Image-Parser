#ifndef COPY_ASSIGNMENT_10_IMAGE_H
#define COPY_ASSIGNMENT_10_IMAGE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <array>

using namespace std;

class Image{

    private:
        string fileName;                                                        //file name string

        struct Pixels{
            int **RGBArray;                                                     //2-D dynamic array
            int width;                                                          //struct member to hold the width of the image
            int height;                                                         //struct member to hold the height of the image
            int maxValue;                                                       //struct member to hold the max pixel value of the image
        };

    public:

        string buffer;                                                          //will hold temp buffers for the values for the magic number and created by string
        string sizeOfWidth;                                                     //will store the total size of the picture
        string sizeOfHeight;                                                    //will store height of image
        string maxPixels;                                                       //will store the max pixel value


        //pixels instance
        Pixels pixels;


        //constructor that takes in a string that represents the file
        Image(string file){
            //opening file and reading the first two non-important lines (of now)
            this->fileName = file;
            ifstream rgbPicture;
            rgbPicture.open(fileName);                                          //open the file for reading (in main, the constructor will take the actual file name
            getline(rgbPicture, buffer, '\n');                                  //reading in the first line
            getline(rgbPicture, buffer, '\n');                                  //reading in the second line

            //retrieving the size of the image
            getline(rgbPicture,sizeOfWidth,' ');                                //reads width
            pixels.width = stoi(sizeOfWidth);                                   //converts to int and passes that into the struct member width
            getline(rgbPicture,sizeOfHeight,'\n');                              //reads next space after white space in the size
            pixels.height = stoi(sizeOfHeight);                                 //converts to int and passes that into the struct member height
            getline(rgbPicture,maxPixels,'\n');                                 //reading max pixel size
            pixels.maxValue = stoi(maxPixels);

            //size of 2D array
            pixels.RGBArray = new int*[3];
            for(int i = 0; i < 3; i++){
                pixels.RGBArray[i] = new int[pixels.width * pixels.height];
            }

            //read all the rgb values into this array
            for(int i = 0; i < 3; i++){
                for (int j = 0; j < (pixels.width*pixels.height); j++){
                    rgbPicture >> pixels.RGBArray[i][j];
                }
            }
            rgbPicture.close();
        }
    //function to create the image
    void createCopperImage();

    //destructor to de-allocate the memory of the object
    ~Image(){
        delete [] pixels.RGBArray;
    }

};


void Image::createCopperImage(){

    //header info
    string magicValue = "P3";
    string creation = "#Created by Tanner Barcelos";

    //opening the new image to write to
    ofstream newImage;
    newImage.open("/Users/tannerbarcelos/OneDrive/CSUEB CompSci/Spring2019/CS201/Homework/another homework 10/newImage.ppm");

    //writing to the new image the default header info
    newImage << magicValue << endl;
    newImage << creation << endl;
    newImage << pixels.width << " " << pixels.height << endl;
    newImage << pixels.maxValue << endl;

    //scaling down red to 0
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < (pixels.width*pixels.height); j+=3){
            pixels.RGBArray[i][j]*=0;
        }
    }

    //write the data to the new file
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < (pixels.width*pixels.height); j++){
            pixels.RGBArray[i][j]*=20;                        //scales every value but we set the reds to 0 so 0*20 still is 0 so our red pixels remain at 0
            newImage << pixels.RGBArray[i][j];
            newImage << " ";
        }
    }
    newImage.close();
}

#endif //COPY_ASSIGNMENT_10_IMAGE_H
