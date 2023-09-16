#include "Header.h"
#include <iostream>
#include <fstream>
using namespace std;

bool Endintga(const string& name) {
    if (name.substr(name.length() - 4) != ".tga") {
        return false;
    }
    else {return true;}
}

bool fileExistence(const string& name) {
    fstream firstfile;
    firstfile.open(name);
    if (firstfile.is_open()) { return true; }
    else { return false; }
}

bool validMethod(const string& name) {
    if (name == "multiply") return true;
    else if (name == "addition") { return true; }
    else if (name == "subtract") { return true; }
    else if (name == "overlay") { return true; }
    else if (name == "screen") { return true; }
    else if (name == "combine") { return true; }
    else if (name == "flip") { return true; }
    else if (name == "onlyred") { return true; }
    else if (name == "onlygreen") { return true; }
    else if (name == "onlyblue") { return true; }
    else if (name == "addred") { return true; }
    else if (name == "addgreen") { return true; }
    else if (name == "addblue") { return true; }
    else if (name == "scalered") { return true; }
    else if (name == "scaleblue") { return true; }
    else if (name == "scalegreen") { return true; }
    else { return false; }
}

bool validNum(const string& num) {
    try { stoi(num); }
    catch (invalid_argument) { return false; }
    return true;
}

int main(int argc, char *argv[]) {

    // checking if help or no arguments passed
    if (argc < 2 || (string)argv[1] == "--help") {
        cout << "Project 2: Image Processing, Spring 2023" << endl << endl;
        cout << "Usage:" << endl;
        cout << "\t./project2.out [output] [firstImage] [method] [...]";
        return 0;
    }

    string output = argv[1];
    // checking name of the output file
    if ((argc < 3) || !Endintga(output)) {
        cout << "Invalid file name.";
        return 0;
    }

    // 0: project, 1: output, 2: tracker, 3: method

    // seeing if 2nd arg (tracking/top image)
    string tracker = argv[2];
    if (!Endintga(tracker)) {
        cout << "Invalid file name.";
        return 0;
    }
    else if (!fileExistence(tracker)){
        cout << "File does not exist.";
        return 0;
    }
    else if (argc < 4) {
        cout << "Invalid file name.";
        return 0;
    }

    Image tracker_i;
    tracker_i.loadFile(tracker);
    Image output_i = tracker_i; //to make sure we're starting on the same image

    int index = 3; // which argument we're on (should be the method)
    while (argc > index) {

        // method validity
        string arg3 = argv[index];
        if (argc < 4 || !validMethod(arg3)) {
            cout << "Invalid method name.";
            return 0;
        }
        string current_arg = argv[index];
        // index = method name

        // start of multiply
        if (current_arg == "multiply") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }

            string next_image = argv[index+1];
            // tga file
            if (!Endintga(next_image)) {
                cout << "Invalid argument, invalid file name.";
                return 0;
            }
            else if (!fileExistence(next_image)) {
                cout << "Invalid argument, file does not exist.";
                return 0;
            }
            else {
                Image image1;
                image1.loadFile(next_image);

                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = image1.multiply(output_i.pixel_vec[i], image1.pixel_vec[i]);
                }
                cout << "Multiplied current " << tracker << " and " << next_image;
            } // end of actual multiplication
            index += 2;
        } // end of multiply

        // start of addition
        if (current_arg == "addition") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string next_image = argv[index+1];
            if (!Endintga(next_image)) {
                cout << "Invalid argument, invalid file name.";
                return 0;
            }
            else if (!fileExistence( next_image)) {
                cout << "Invalid argument, file does not exist.";
                return 0;
            }
            else {
                Image image1;
                image1.loadFile(next_image);

                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = image1.addition(output_i.pixel_vec[i], image1.pixel_vec[i]);
                }
                cout << "Added current " << tracker << " and " << next_image;
            } // end of actual addition
            index += 2;
        } // end of addition

        // start of subtract
        if (current_arg == "subtract") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string next_image = argv[index+1];
            if (!Endintga(next_image)) {
                cout << "Invalid argument, invalid file name.";
                return 0;
            }
            else if (!fileExistence(next_image)){
                cout << "Invalid argument, file does not exist.";
                return 0;
                }
            else {
                Image image1;
                image1.loadFile(next_image);

                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = image1.subtract(output_i.pixel_vec[i], image1.pixel_vec[i]);
                }
                cout << "Subtracted current " << tracker << " and " << next_image;
            } // end of actual subtraction
            index += 2;
        } // end of subtract

        // start of screen
        if (current_arg == "screen") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string next_image = argv[index+1];
            if (!Endintga(next_image)) {
                cout << "Invalid argument, invalid file name.";
                return 0;
            }
            else if (!fileExistence(next_image)) {
                cout << "Invalid argument, file does not exist.";
                return 0;
            }
            else {
                Image image1;
                image1.loadFile(next_image);

                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = image1.screen(output_i.pixel_vec[i], image1.pixel_vec[i]);
                }
                cout << "Screened current " << tracker << " and " << next_image;
            } // end of actual screening
            index += 2;
        } // end of screen

        // start of overlay
        if (current_arg == "overlay") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string next_image = argv[index+1];
            if (!Endintga(next_image)) {
                cout << "Invalid argument, invalid file name.";
                return 0;
            }
            else if (!fileExistence(next_image)){
                cout << "Invalid argument, file does not exist.";
                return 0;
            }
            else {
                Image image1;
                image1.loadFile(next_image);

                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = image1.overlay(output_i.pixel_vec[i], image1.pixel_vec[i]);
                }
                cout << "Overlay-ed current " << tracker << " and " << next_image;
            } // end of actual overlaying
            index += 2;
        } // end of overlay

        // start of addred
        if (current_arg == "addred") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string s_num = argv[index + 1];
            float num;
            if (!validNum(s_num)) {
                cout << "Invalid argument, expected number.";
                return 0;
            }
            else {
                num = stof(s_num);
                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = output_i.addred(output_i.pixel_vec[i], num);
                }
            }
            cout << "Added " << num << " red to " << tracker;
            index += 2;
        } // end of addred

        // start of addblue
        if (current_arg == "addblue") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string s_num = argv[index + 1];
            float num;
            if (!validNum(s_num)) {
                cout << "Invalid argument, expected number.";
                return 0;
            }
            else {
                num = stof(s_num);
                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = output_i.addblue(output_i.pixel_vec[i], num);
                }
            }
            cout << "Added " << num << " blue to " << tracker;
            index += 2;
        } // end of addblue

        // start of addgreen
        if (current_arg == "addgreen") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string s_num = argv[index + 1];
            float num;
            if (!validNum(s_num)) {
                cout << "Invalid argument, expected number.";
                return 0;
            }
            else {
                num = stof(s_num);
                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = output_i.addgreen(output_i.pixel_vec[i], num);
                }
            }
            cout << "Added " << num << " green to " << tracker;
            index += 2;
        } // end of addgreen

        // start of scalered
        if (current_arg == "scalered") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string s_num = argv[index + 1];
            float num;
            if (!validNum(s_num)) {
                cout << "Invalid argument, expected number.";
                return 0;
            }
            else {
                num = stof(s_num);
                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = output_i.scalered(output_i.pixel_vec[i], num);
                }
            }
            cout << "Scaled " << tracker << "'s red by " << num;
            index += 2;
        } // end of scale red

        // start of scaleblue
        if (current_arg == "scaleblue") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string s_num = argv[index + 1];
            float num;
            if (!validNum(s_num)) {
                cout << "Invalid argument, expected number.";
                return 0;
            }
            else {
                num = stof(s_num);
                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = output_i.scaleblue(output_i.pixel_vec[i], num);
                }
            }
            cout << "Scaled " << tracker << "'s blue by " << num;
            index += 2;
        } // end of scale blue

        // start of scalegreen
        if (current_arg == "scalegreen") {
            if (argc <= index+1) {
                cout << "Missing argument.";
                return 0;
            }
            string s_num = argv[index + 1];
            float num;
            if (!validNum(s_num)) {
                cout << "Invalid argument, expected number.";
                return 0;
            }
            else {
                num = stof(s_num);
                for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                    output_i.pixel_vec[i] = output_i.scalegreen(output_i.pixel_vec[i], num);
                }
            }
            cout << "Scaled " << tracker << "'s green by " << num;
            index += 2;
        } // end of scale green

        // start of only red
        if (current_arg == "onlyred") {
            for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                output_i.pixel_vec[i] = output_i.onlyred(output_i.pixel_vec[i]);
            }
            cout << "Red channel retrieved from " << tracker;
            index += 1;
        } // end of only red

        // start of only green
        if (current_arg == "onlygreen") {
            for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                output_i.pixel_vec[i] = output_i.onlygreen(output_i.pixel_vec[i]);
            }
            cout << "Green channel retrieved from " << tracker;
            index += 1;
        } // end of only green

        // start of only blue
        if (current_arg == "onlyblue") {
            for(int i = 0; i < output_i.pixel_vec.size(); i++) {
                output_i.pixel_vec[i] = output_i.onlyblue(output_i.pixel_vec[i]);
            }
            cout << "Blue channel retrieved from " << tracker;
            index += 1;
        } // end of only blue

        // start of flip
        if (current_arg == "flip") {
            output_i.flip();
            cout << "Flipped " << tracker;
            index ++;
        } // end of flip

        // start of combine
        if (current_arg == "combine") {
            if (argc <= index + 2) {
                cout << "Missing argument.";
                return 0;
            }
            for (int i = 0; i < 2; i++) {
                string next_image = argv[index + 1 + i];
                if (!Endintga(next_image)) {
                    cout << "Invalid argument, invalid file name.";
                    return 0;
                } else if (!fileExistence(next_image)) {
                    cout << "Invalid argument, file does not exist.";
                    return 0;
                }
            }
            string green = argv[index + 1];
            Image green_i;
            green_i.loadFile(green);

            string blue = argv[index + 2];
            Image blue_i;
            blue_i.loadFile(blue);

            for (int i = 0; i < output_i.pixel_vec.size(); i++) {
                output_i.pixel_vec[i] = output_i.combine(output_i.pixel_vec[i], blue_i.pixel_vec[i], green_i.pixel_vec[i]);
            }
            cout << "Combined " << output << ", " << green << ", and " << blue;
            index += 3;
        } // end of combine

    } // end of the while loop
    output_i.writeFile(output);
}