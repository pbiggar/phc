void int_test(int a, int b) {
    int x, y, z;

    x = 2;
    y = (unsigned int)3;
    z = (int)4.0;

    x += y - a * b;
    y += z;
    z = z / 2;
}
