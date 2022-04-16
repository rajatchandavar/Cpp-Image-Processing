#include "image.h"

int main(){
    image test("test.jpg");
    test.write("new.png");

    image copy(test);

    //First row of copy to black
    for (int i = 0; i < copy.w * copy.channels; ++i){
        copy.data[i] = 0;
    }
    copy.write("copy.png");

    image blank(1000,1000,3);
    blank.write("blank.jpg");
    return 0;
}