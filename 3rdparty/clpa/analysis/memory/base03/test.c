// From /openssh-3.9p1/openbsd-compat/vis.c

typedef unsigned char u_char;
typedef unsigned int u_int;

char *
vis(dst, c, flag, nextc)
        register char *dst;
        char c, nextc;
        register int flag;
{
        if ((((u_int)(c) <= 255 && isascii((u_char)(c)) && isgraph((u_char)(c))) || ((flag & 0x04) == 0 && (c) == ' ') || ((flag & 0x08) == 0 && (c) == '\t') || ((flag & 0x10) == 0 && (c) == '\n') || ((flag & 0x20) && ((c) == '\b' || (c) == '\007' || (c) == '\r' || isgraph((u_char)(c)))))) {
                *dst++ = c;
                if (c == '\\' && (flag & 0x40) == 0)
                        *dst++ = '\\';
                *dst = '\0';
                return (dst);
        }

        if (flag & 0x02) {
                switch(c) {
                case '\n':
                        *dst++ = '\\';
                        *dst++ = 'n';
                        goto done;
                case '\r':
                        *dst++ = '\\';
                        *dst++ = 'r';
                        goto done;
                case '\b':
                        *dst++ = '\\';
                        *dst++ = 'b';
                        goto done;
                case '\a':
                        *dst++ = '\\';
                        *dst++ = 'a';
                        goto done;
                case '\v':
                        *dst++ = '\\';
                        *dst++ = 'v';
                        goto done;
                case '\t':
                        *dst++ = '\\';
                        *dst++ = 't';
                        goto done;
                case '\f':
                        *dst++ = '\\';
                        *dst++ = 'f';
                        goto done;
                case ' ':
                        *dst++ = '\\';
                        *dst++ = 's';
                        goto done;
                case '\0':
                        *dst++ = '\\';
                        *dst++ = '0';
                        if ((((u_char)(nextc)) >= '0' && ((u_char)(nextc)) <= '7')) {
                                *dst++ = '0';
                                *dst++ = '0';
                        }
                        goto done;
                }
        }

        if (((c & 0177) == ' ') || (flag & 0x01)) {
                *dst++ = '\\';
                *dst++ = ((u_char)c >> 6 & 07) + '0';
                *dst++ = ((u_char)c >> 3 & 07) + '0';
                *dst++ = ((u_char)c & 07) + '0';
                goto done;
        }
        if ((flag & 0x40) == 0)
                *dst++ = '\\';
        if (c & 0200) {
                c &= 0177;
                *dst++ = 'M';
        }

        if (iscntrl(c)) {
                *dst++ = '^';
                if (c == 0177)
                        *dst++ = '?';
                else
                        *dst++ = c + '@';
        } else {
                *dst++ = '-';
                *dst++ = c;
        }

done:
        *dst = '\0';
        return (dst);
}
