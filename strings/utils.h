String setCharAtSafe(String s, char chr, int idx) {
    int length = s.length();

    while (length++ <= idx) {
        s.concat(" ");
    }

    s.setCharAt(idx, chr);

    return s;
}

String generateEmptyString(int length) {
    String empty = "";

    while (length-- >= 0) {
        empty.concat(" ");
    }

    return empty;
}