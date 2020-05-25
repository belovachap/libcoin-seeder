#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <libcoin-seeder/version.h>
#include <libcoin-seeder/coin-seeder.h>

#ifdef _WIN32
#define tmpfile mytmpfile
static FILE *mytmpfile ();
#endif

int main ()
{
    // to_little_endian
    {
        uchar *le = to_little_endian(0xAABBCCDD);
        assert(le[0] == 0xDD);
        assert(le[1] == 0xCC);
        assert(le[2] == 0xBB);
        assert(le[3] == 0xAA);
        free(le);
    }

    // from_little_endian
    {
        uchar b[4] = {0xDD, 0xCC, 0xBB, 0xAA};
        uint32_t i = from_little_endian(b);
        assert(i == 0xAABBCCDD);
    }

    return 0;
}

#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>
#include <io.h>

FILE *mytmpfile ()
{
  char d[MAX_PATH + 1], p[MAX_PATH + 1];
  if (GetTempPathA (sizeof (d), d) == 0 ||
      GetTempFileNameA (d, "tmp", 0, p) == 0)
    return NULL;

  HANDLE h = CreateFileA (p,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          CREATE_ALWAYS,
                          FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE,
                          NULL);
  if (h == INVALID_HANDLE_VALUE)
    return NULL;

  int fd = _open_osfhandle ((intptr_t) h, _O_RDWR);
  if (fd == -1)
    return NULL;

  FILE *f = _fdopen (fd, "wb+");
  if (f == NULL)
    _close (fd);

  return f;
}
#endif
