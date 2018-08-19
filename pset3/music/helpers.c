// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //By subtracting the ascii value of 0 (aka 48), it would result the differences between
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';

    //Divide the fraction itself (8) will result an eigtht of the number
    //Then multiply it by how many eigtht there are will
    return (8 / denominator) * numerator;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double frequency = 0.0;

    //Get the octave which is the last char
    int octave = note[strlen(note) - 1] - '0'; //get last char by lenght - 1- Using ascii values we can find the difference between each octave by substracting ascii value of 0

    //Check the note letter and calculate the frequency
    //TODO: Maybe this can be change into a switch statement?
    if (note[0] == 'A')
    {
        frequency = 440.0;
    }
    else if (note[0] == 'B')
    {
        frequency = 440.0 * (pow(2.0, (2.0 / 12.0))); //Multiply 440 to the power of 2^1/12
    }
    else if (note[0] == 'C')
    {
        frequency = 440.0 / (pow(2.0, (9.0 / 12.0))); //Divide 440 to the power of whatever to go down
    }
    else if (note[0] == 'D')
    {
        frequency = 440.0 / (pow(2.0, (7.0 / 12.0)));
    }
    else if (note[0] == 'E')
    {
        frequency = 440.0 / (pow(2.0, (5.0 / 12.0)));
    }
    else if (note[0] == 'F')
    {
        frequency = 440.0 / (pow(2.0, (4.0 / 12.0)));
    }
    else if (note[0] == 'G')
    {
        frequency = 440.0 / (pow(2.0, (2.0 / 12.0)));
    }

    //Adjust for different octave
    //Check if its over 4 or under 4, if so multiply or divide how many times of the octave's difference
    if (octave > 4)
    {
        for (int i = 0; i < octave - 4; i++)
        {
            frequency = frequency * 2.0; //Multiply itself by 2
        }
    }
    else if (octave < 4)
    {
        for (int i = 0; i < 4 - octave; i++)
        {
            frequency = frequency / 2.0; //Divide ifself by 2
        }
    }

    //Check if there is an accidental
    if (note[1] == '#')
    {
        frequency = frequency * pow(2.0, (1.0 / 12.0));
    }
    else if (note[1] == 'b')
    {
        frequency = frequency / pow(2.0, (1.0 / 12.0));
    }

    //Round the frequency to a clear number
    int returnValue = round(frequency);

    return returnValue;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}
