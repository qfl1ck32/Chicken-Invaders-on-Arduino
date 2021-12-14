short getNumberOfDigits(short number) {
    if (number == 0) return 1;

    short answer = 0;

    while (number) {
        ++answer;
        number /= 10;
    }

    return answer;
}
