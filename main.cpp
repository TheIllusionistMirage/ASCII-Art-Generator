/*************************************************************
*                    ASCII ART GENERATOR                     *
*                                                            *
*   (C) Koushtav Chakrabarty a.k.a. The Illusionist Mirage   *
*                                                            *
**************************************************************
*                                                            *
*     A simple, image to ASCII art converter. Requires       *
*     SFML to compile. Enjoy!!!                              *
*                                                            *
*     ( AND MAKE SURE YOU ZOOM OUT TO FULL EXTENT IN THE     *
*     TEXT EDITOR YOU USE TO VIEW THE OUTPUT )               *
*                                                            *
*     If you want the output as HTML files, just uncomment   *
*     lines 99 to 101 and add them inside the <pre></pre>    *
*     tags of the following HTML file and save as .html :    *
*                                                            *
*     <!doctype html>                                        *
*     <html>                                                 *
*       <body>                                               *
*         <pre class="white"                                 *
*          style="font: 5px/5px monospace;                   *
*          text-align: center;">                             *
*                                                            *
*             ...YOUR OUTPUT GOES HERE...                    *
*                                                            *
*         </pre>                                             *
*       </body>                                              *
*     </html>                                                *
*                                                            *
*************************************************************/


#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

using Uint8 = unsigned char;

int main(int argc, char *argv[])
{
    sf::Image inputImage;
    std::ofstream output;
    std::string fileName;

    const unsigned char *pixelPtr = nullptr;

    const std::array<char, 34> charSet = {
         '@', '#', '9', '8', '&',
         '6', '5', '4', '0', '3',
         '7', '?', 'o', '>', '<',
         '2', ']', '[', '\\', '/',
         '1', '!', ';', ':', '+',
         '*', '~', '-', '`', '"',
         '\'', ',', '.', ' '
    };

    try
    {
        std::cout << "Enter image file name(including extension) : ";
        std::getline(std::cin, fileName);

        /*if(argc != 2)
            throw std::runtime_error("ERROR :: No input image file specified!");

        fileName = argv[1];*/

        if(!inputImage.loadFromFile(fileName))
            throw std::runtime_error("ERROR :: Unable to open image file \"" + fileName + "\"!");

        pixelPtr = inputImage.getPixelsPtr();

        output.open("output.txt", std::ios::out | std::ios::ate);
        if(!output)
            throw std::runtime_error("ERROR :: Unable to create output file!");

        for(unsigned y = 0; y < inputImage.getSize().y; y++)
        {
            for(unsigned x = 0; x < inputImage.getSize().x; x++)
            {
                int outputChar = ( (pixelPtr[y * inputImage.getSize().x * 4 + x * 4 + 0])
                                 + (pixelPtr[y * inputImage.getSize().x * 4 + x * 4 + 1])
                                 + (pixelPtr[y * inputImage.getSize().x * 4 + x * 4 + 2]) ) / 3;

                outputChar /= (255 / charSet.size());

                if(outputChar >= charSet.size())
                    outputChar = charSet.size() - 1;

                if(outputChar < 0)
                    outputChar = 0;

                /*
                 Uncomment this block ony if you want the output to be HTML specific.
                */
                /*if(charSet[outputChar] == '&')
                    output << "&amp";
                else if(charSet[outputChar] == '<')
                    output << "&lt";
                else if(charSet[outputChar] == '>')
                    output << "&gt";
                else*/
                    output << charSet[outputChar];
            }
            output << std::endl;
        }
        
        std::cout << "Output successflly produced in 'output.txt'!" << std::endl;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
