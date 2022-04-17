#include "image.h"

int main(){
    image test("images/test.jpg");
    image gray_avg(test);

    gray_avg.grayscale_avg(); 
    gray_avg.write("images/gray_avg.png");

    test.colormask(0,1, 0);
    test.write("images/Green_test.png");

    image test2("images/diff_test.jpg");
    image diff(test);
    diff.diffmap(test2);
    diff.write("images/diff_result.png");
    return 0;
}