#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Pixels.h"
#include <cmath>
#pragma once
using namespace std;

const int ReadWidth(string filePath); // function that finds the width of the image
const int ReadHeight(string filePath); // function that finds the height of the image
Header ReadHeader(string filePath);
void WriteImage(string filePath, Header headerObj, char * imageData);
char * ReadImageData(string filePath, Header headerObj);
char * MultiplyImageData(char * layerOne, char * layerTwo, Header headerObj);
char * SubtractImageData(char * layerOne, char * layerTwo, Header headerObj);
char * ScreenImageData(char * layerOne, char * layerTwo, Header headerObj);
char * OverlayImageData(char * layerOne, char * layerTwo, Header headerObj);
char * AddToChannel(char * layerOne, Header headerObj,int channel, float add);
char * ScalarToChannel(char * layerOne, Header headerObj,int channel, float scalar);
char * CopyChannel(char * layerOne, Header headerObj, int copyChanel);
char * CopyLayers(char * layerOne, char * layerTwo, char * layerThree, Header headerObj);
char * RotateImage(char * layerOne, Header headerObj);
bool ImageComparison(string inputPath, string examplePath);


int main(){

    //Test One
    Header headerObject = ReadHeader("input/layer1.tga");
    char * layerOne = ReadImageData("input/layer1.tga",headerObject);
    char * patternOne = ReadImageData("input/pattern1.tga",headerObject);
    char * pixImage = MultiplyImageData(layerOne,patternOne,headerObject);
    WriteImage("output/part1.tga",headerObject,pixImage);

    //Test Two
    Header headerObject2 = ReadHeader("input/layer2.tga");
    char * layerTwo = ReadImageData("input/layer2.tga",headerObject2);
    char * carPart = ReadImageData("input/car.tga",headerObject2);
    char * pixImage2 = SubtractImageData(layerTwo,carPart, headerObject);
    WriteImage("output/part2.tga",headerObject2,pixImage2);

    //Test Three
    char * patternTwo = ReadImageData("input/pattern2.tga",headerObject);
    char * tempPixImage = MultiplyImageData(patternTwo,layerOne,headerObject);
    char * textPart = ReadImageData("input/text.tga",headerObject);
    char * pixImage3 = ScreenImageData(tempPixImage,textPart,headerObject);
    WriteImage("output/part3.tga",headerObject,pixImage3);

    //Test Four
    Header headerObject3 = ReadHeader("input/circles.tga");
    char * circlePart = ReadImageData("input/circles.tga",headerObject3);
    tempPixImage = MultiplyImageData(layerTwo,circlePart,headerObject3);
    char * pixImage4 = SubtractImageData(patternTwo,tempPixImage,headerObject3);
    WriteImage("output/part4.tga",headerObject3,pixImage4);

    //Test Five
    char * pixImage5 = OverlayImageData(layerOne,patternOne,headerObject);
    WriteImage("output/part5.tga",headerObject,pixImage5);

    //Test Six
    char * pixImage6 = AddToChannel(carPart,headerObject2,1,200);
    WriteImage("output/part6.tga",headerObject2,pixImage6);

    //Test Seven
    tempPixImage = ScalarToChannel(carPart,headerObject2,2,4);
    char * pixImage7 = ScalarToChannel(tempPixImage,headerObject2,0,0);
    WriteImage("output/part7.tga",headerObject2,pixImage7);

    //Test Eight
    char * pixImageRed =CopyChannel(carPart,headerObject2,2);
    WriteImage("output/part8_r.tga",headerObject2,pixImageRed);

    char * pixImageBlue = CopyChannel(carPart,headerObject2,0);
    WriteImage("output/part8_b.tga",headerObject2,pixImageBlue);

    char * pixImageGreen = CopyChannel(carPart,headerObject2,1);
    WriteImage("output/part8_g.tga",headerObject2,pixImageGreen);

    Header headerObject4 = ReadHeader("input/layer_green.tga");
    char * layerGreen = ReadImageData("input/layer_green.tga",headerObject4);
    char * layerBlue = ReadImageData("input/layer_blue.tga",headerObject4);
    char * layerRed = ReadImageData("input/layer_red.tga",headerObject4);
    char * pixImage9 = CopyLayers(layerBlue,layerGreen,layerRed,headerObject4);
    WriteImage("output/part9.tga",headerObject4,pixImage9);

    Header headerObject5 = ReadHeader("input/text2.tga");
    char * textImage2 = ReadImageData("input/text2.tga", headerObject5);
    char * pixImage10 = RotateImage(textImage2,headerObject5);
    WriteImage("output/part10.tga",headerObject5,pixImage10);

    //Test Images
    int testResult;
    if(ImageComparison("output/part1.tga","examples/EXAMPLE_part1.tga"))
    {
        cout << "Test 1 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 1 ..... Failed";
    }

    if(ImageComparison("output/part2.tga","examples/EXAMPLE_part2.tga"))
    {
        cout << "Test 2 ..... Passed"<<endl;
        testResult++;
    }
    else{
        cout << "Test 2 ..... Failed";
    }

    if(ImageComparison("output/part3.tga","examples/EXAMPLE_part3.tga"))
    {
        cout << "Test 3 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 3 ..... Failed";
    }

    if(ImageComparison("output/part4.tga","examples/EXAMPLE_part4.tga"))
    {
        cout << "Test 4 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 4 ..... Failed";

    }

    if(ImageComparison("output/part5.tga","examples/EXAMPLE_part5.tga"))
    {
        cout << "Test 5 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 5 ..... Failed";
    }

    if(ImageComparison("output/part6.tga","examples/EXAMPLE_part6.tga"))
    {
        cout << "Test 6 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 6 ..... Failed";
    }

    if(ImageComparison("output/part7.tga","examples/EXAMPLE_part7.tga"))
    {
        cout << "Test 7 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 7 ..... Failed";
    }

    if(ImageComparison("output/part8_b.tga","examples/EXAMPLE_part8_b.tga"))
    {
        cout << "Test 8 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 8 ..... Failed";
    }
    if(ImageComparison("output/part8_g.tga","examples/EXAMPLE_part8_g.tga"))
    {
        cout << "Test 9 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 9 ..... Failed";
    }
    if(ImageComparison("output/part8_r.tga","examples/EXAMPLE_part8_r.tga"))
    {
        cout << "Test 10 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 10 ..... Failed";
    }

    if(ImageComparison("output/part9.tga","examples/EXAMPLE_part9.tga"))
    {
        cout << "Test 11 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 11 ..... Failed";
    }

    if(ImageComparison("output/part10.tga","examples/EXAMPLE_part10.tga"))
    {
        cout << "Test 12 ..... Passed" << endl;
        testResult++;
    }
    else{
        cout << "Test 12 ..... Failed";
    }
    cout << "Test Results: " << testResult << " / 12";
    return 0;
}

bool ImageComparison(string myPath, string examplePath)
{
    bool flag = true;
    Header myImageHeader = ReadHeader(myPath);
    char * myImage = ReadImageData(myPath,myImageHeader);

    Header exampleHeader = ReadHeader(examplePath);
    char * exampleImage = ReadImageData(examplePath,exampleHeader);
    if(myImageHeader.bitsPerPixel != exampleHeader.bitsPerPixel)
    {
        flag = false;
    }
    if(myImageHeader.colorMapDepth != exampleHeader.colorMapDepth)
    {
        flag = false;
    }
    if(myImageHeader.colorMapLength != exampleHeader.colorMapLength)
    {
        flag = false;
    }
    if(myImageHeader.colorMapOrigin != exampleHeader.colorMapOrigin)
    {
        flag = false;
    }
    if(myImageHeader.colorMapType != exampleHeader.colorMapType)
    {
        flag = false;
    }
    if(myImageHeader.dataTypeCode != exampleHeader.dataTypeCode)
    {
        flag = false;
    }
    if(myImageHeader.height!= exampleHeader.height)
    {
        flag = false;
    } if(myImageHeader.width != exampleHeader.width)
    {
        flag = false;
    }
    if(myImageHeader.imageDescriptor != exampleHeader.imageDescriptor)
    {
        flag = false;
    }
    if(myImageHeader.xOrigin!= exampleHeader.xOrigin)
    {
        flag = false;
    }
    if(myImageHeader.yOrigin!= exampleHeader.yOrigin)
    {
        flag = false;
    }
    for(unsigned int i = 0; i < myImageHeader.width * myImageHeader.height * 3; i++)
    {
        if(myImage[i] != exampleImage[i])
        {
            flag = false;
        }
    }
    return flag;

}
char * RotateImage(char * layerOne, Header headerObj)
{
    unsigned char storeMe;
    float lOne;
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    for(unsigned int i = 2; i < (headerObj.width * headerObj.height) * 3; i = i+3)
    {
        newImage[i] = layerOne[(headerObj.width * headerObj.height * 3) - 1 - i + 2];
        newImage[i - 1] = layerOne[(headerObj.width * headerObj.height * 3)- 1 - i + 1];
        newImage[i - 2] = layerOne[(headerObj.width * headerObj.height * 3)- 1 - i];
    }

    return newImage;
}
char * CopyLayers(char * layerOne, char * layerTwo, char * layerThree, Header headerObj)
{
    unsigned char storeMe;
    float lOne;
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
        storeMe = (unsigned char) layerOne[i];
        lOne = (float) storeMe;
        newImage[i] = (unsigned char) lOne;
    }
    for(unsigned int i = 1; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
        storeMe = (unsigned char) layerTwo[i];
        lOne = (float) storeMe;
        newImage[i] = (unsigned char) lOne;
    }
    for(unsigned int i = 2; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
        storeMe = (unsigned char) layerThree[i];
        lOne = (float) storeMe;
        newImage[i] = (unsigned char) lOne;
    }
    return newImage;


}

char * CopyChannel(char * layerOne, Header headerObj, int copyChanel)
{
    unsigned char storeMe;
    float lOne;
    float newL;
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
    {
        storeMe = (unsigned char)layerOne[i];
        lOne = (float)storeMe;
        newImage[i] = (unsigned char) lOne;
    }
    if(copyChanel == 0) {
        for (unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
           newL = lOne;
            newImage[i] = (unsigned char) newL;
            newImage[i + 1] = (unsigned char) newL;
            newImage[i + 2] = (unsigned char) newL;
        }
    }
    if(copyChanel == 1) {
        for (unsigned int i = 1; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
            newL = lOne;
            newImage[i] = (unsigned char) newL;
            newImage[i - 1] = (unsigned char) newL;
            newImage[i + 1] = (unsigned char) newL;
        }
    }
    if(copyChanel == 2) {
        for (unsigned int i = 2; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
            newL = lOne;
            newImage[i] = (unsigned char) newL;
            newImage[i - 1] = (unsigned char) newL;
            newImage[i - 2] = (unsigned char) newL;
        }
    }
    return newImage;
}
char * ScalarToChannel(char * layerOne, Header headerObj,int channel, float scalar)
{
    unsigned char storeMe;
    float lOne;
    float newL;
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
    {
        storeMe = (unsigned char)layerOne[i];
        lOne = (float)storeMe;
        newImage[i] = (unsigned char) lOne;
    }
    if(channel == 0) {
        for (unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
            newL = lOne * scalar;
            if (newL > 255) {
                newL = 255;
            }
            if (newL < 0) {
                newL = 0;
            }
            newImage[i] = (unsigned char) newL;
        }
    }
    if(channel == 1) {
        for (unsigned int i = 1; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
            newL = lOne * scalar;
            if (newL > 255) {
                newL = 255;
            }
            if (newL < 0) {
                newL = 0;
            }
            newImage[i] = (unsigned char) newL;
        }
    }
    if(channel == 2){
        for(unsigned int i = 2; i < (headerObj.width * headerObj.height) * 3; i = i + 3)
        {
            storeMe = (unsigned char)layerOne[i];
            lOne = (float)storeMe;
            newL = lOne * scalar;
            if(newL > 255)
            {
                newL = 255;
            }
            if(newL < 0)
            {
                newL = 0;
            }
            newImage[i] = (unsigned char) newL;
        }}
    return newImage;
}

char * AddToChannel(char * layerOne, Header headerObj,int channel, float add)
{
    unsigned char storeMe;
    float lOne;
    float newL;
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
    {
        storeMe = (unsigned char)layerOne[i];
        lOne = (float)storeMe;
        newImage[i] = (unsigned char) lOne;
    }
    if(channel == 0) {
        for (unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
            newL = lOne + add;
            if (newL > 255) {
                newL = 255;
            }
            if (newL < 0) {
                newL = 0;
            }
            newImage[i] = (unsigned char) newL;
        }
    }
    if(channel == 1) {
        for (unsigned int i = 1; i < (headerObj.width * headerObj.height) * 3; i = i + 3) {
            storeMe = (unsigned char) layerOne[i];
            lOne = (float) storeMe;
            newL = lOne + add;
            if (newL > 255) {
                newL = 255;
            }
            if (newL < 0) {
                newL = 0;
            }
            newImage[i] = (unsigned char) newL;
        }
    }
    if(channel == 2){
    for(unsigned int i = 2; i < (headerObj.width * headerObj.height) * 3; i = i + 3)
    {
        storeMe = (unsigned char)layerOne[i];
        lOne = (float)storeMe;
        newL = lOne + add;
        if(newL > 255)
        {
            newL = 255;
        }
        if(newL < 0)
        {
            newL = 0;
        }
        newImage[i] = (unsigned char) newL;
    }}
    return newImage;
}

char * OverlayImageData(char * layerOne, char * layerTwo, Header headerObj)
{
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    unsigned char storeMe;
    unsigned char storeMe2;
    float lOne;
    float lTwo;
    float newL;
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
    {
        storeMe = (unsigned char)layerOne[i];
        storeMe2 = (unsigned char)layerTwo[i];
        lOne = (float)storeMe;
        lTwo = (float)storeMe2;
        lOne /= 255.0;
        lTwo /= 255.0;
        if(lTwo > 0.5) {
            newL = 1 - (2*(1 - lOne) * (1 - lTwo));
        }
        if(lTwo <= 0.5){
            newL = lOne * lTwo * 2;
        }
        newL = newL * 255;
        newL = newL +0.5f;

        newImage[i] = (unsigned char) newL;

    }
    return newImage;
}
char * ScreenImageData(char * layerOne, char * layerTwo, Header headerObj)
{
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    unsigned char storeMe;
    unsigned char storeMe2;
    float lOne;
    float lTwo;
    float newL;
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
    {
        storeMe = (unsigned char)layerOne[i];
        storeMe2 = (unsigned char)layerTwo[i];
        lOne = (float)storeMe;
        lTwo = (float)storeMe2;
        lOne /= 255.0;
        lTwo /= 255.0;

        newL = 1 - ((1 - lOne) * (1 - lTwo ));
        newL = newL * 255;
        newL = newL +0.5f;

        newImage[i] = (unsigned char) newL;

    }

    return newImage;
}

char * SubtractImageData(char * layerOne, char * layerTwo, Header headerObj)
{
    char * newImage = new char [headerObj.width * headerObj.height *  3];
    unsigned char storeMe;
    unsigned char storeMe2;
    float lOne;
    float lTwo;
    float newL;
    for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
    {
        storeMe = (unsigned char)layerOne[i];
        storeMe2 = (unsigned char)layerTwo[i];
        lOne = (float)storeMe;
        lTwo = (float)storeMe2;

        newL = lTwo - lOne;
        if(newL < 0)
        {
            newL = 0;
        }
        newImage[i] = (unsigned char) newL;

    }
return newImage;

}
char * MultiplyImageData(char * layerOne, char * layerTwo, Header headerObj)
{
   char * newImage = new char [headerObj.width * headerObj.height *  3];
   unsigned char storeMe;
   unsigned char storeMe2;
   float lOne;
   float lTwo;
   float newL;
   for(unsigned int i = 0; i < (headerObj.width * headerObj.height) * 3; i++)
   {
       storeMe = (unsigned char)layerOne[i];
       storeMe2 = (unsigned char)layerTwo[i];
        lOne = (float)storeMe;
        lTwo = (float)storeMe2;
       lOne /= 255.0;
       lTwo /= 255.0;

       newL = lOne * lTwo;
       newL = newL * 255;
       newL = newL +0.5f;

       newImage[i] = (unsigned char) newL;

   }

    return newImage;
}


char * ReadImageData(string filePath, Header headerObj)
{
    fstream file1(filePath,ios_base::in);

    if (! file1.good()) {
	cout << "problem: " << filePath << endl;
	cout.flush();
	throw 0;
    }

    char * pixImage = new  char [headerObj.width * headerObj.height * 3];

    file1.seekg(18);

    file1.read(pixImage, headerObj.width * headerObj.height * 3);
    return pixImage;


}

Header ReadHeader(string filePath)
{
    Header headerObject;
    fstream file2(filePath, ios_base::in);
    file2.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file2.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file2.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file2.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file2.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file2.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file2.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file2.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file2.read((char*)&headerObject.width, sizeof(headerObject.width));
    file2.read((char*)&headerObject.height, sizeof(headerObject.height));
    file2.read((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file2.read((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    return headerObject;
}

void WriteImage(string filePath, Header headerObj, char * imageData)
{
    ofstream file1(filePath, ios_base::binary);
    Header headerObject = headerObj;

    file1.write(&headerObject.idLength, sizeof(headerObject.idLength));
    file1.write(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file1.write(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file1.write((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file1.write((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file1.write(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file1.write((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file1.write((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file1.write((char*)&headerObject.width, sizeof(headerObject.width));
    file1.write((char*)&headerObject.height, sizeof(headerObject.height));
    file1.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    file1.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

    file1.write(imageData , headerObject.width * headerObject.height * 3);
}

const int ReadHeight(string filePath)
{
    fstream file1(filePath, ios_base::in);
    Header headerObject;


    file1.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file1.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file1.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file1.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file1.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file1.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file1.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file1.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file1.read((char*)&headerObject.width, sizeof(headerObject.width));
    file1.read((char*)&headerObject.height, sizeof(headerObject.height));

    const int fileHeight= (int) headerObject.height;

    return fileHeight;
}

const int ReadWidth(string filePath)
{

    fstream file1(filePath, ios_base::in); // opens the file from the given path
    Header headerObject;


    file1.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file1.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file1.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file1.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    file1.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    file1.read(&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    file1.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    file1.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    file1.read((char*)&headerObject.width, sizeof(headerObject.width)); // Reads the width
    file1.read((char*)&headerObject.height, sizeof(headerObject.height));

    const int fileWidth = (int) headerObject.width;

    return fileWidth; // returns width of the file
}
