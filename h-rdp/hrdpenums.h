#ifndef HRDPENUMS_H
#define HRDPENUMS_H

enum class HMode{
    Home,
    Office,
    Unknown
};

enum class HConnectionChannels{
    Passcode,
    LDAP,
    Video,
    Mouse,
    Keyboard
};

#endif // HRDPENUMS_H
