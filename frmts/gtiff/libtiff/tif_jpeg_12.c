
#include "tiffiop.h"

#if defined(JPEG_DUAL_MODE_8_12)

#define TIFFInitJPEG TIFFInitJPEG_12
#define TIFFJPEGIsFullStripRequired TIFFJPEGIsFullStripRequired_12

int TIFFInitJPEG_12(TIFF *tif, int scheme);

#include LIBJPEG_12_PATH

#include "tif_jpeg.c"

int TIFFReInitJPEG_12(TIFF *tif, const JPEGOtherSettings *otherSettings,
                      int scheme, int is_encode) {
  JPEGState *sp;
  uint8_t *new_tif_data;

  (void)scheme;
  assert(scheme == COMPRESSION_JPEG);

  new_tif_data = (uint8_t *)_TIFFrealloc(tif->tif_data, sizeof(JPEGState));

  if (new_tif_data == NULL) {
    TIFFErrorExt(tif->tif_clientdata, "TIFFReInitJPEG_12",
                 "No space for JPEG state block");
    return 0;
  }

  tif->tif_data = new_tif_data;
  _TIFFmemset(tif->tif_data, 0, sizeof(JPEGState));

  TIFFInitJPEGCommon(tif);

  sp = JState(tif);
  sp->otherSettings = *otherSettings;

  if (is_encode)
    return JPEGSetupEncode(tif);
  else
    return JPEGSetupDecode(tif);
}

#endif /* defined(JPEG_DUAL_MODE_8_12) */

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 8
 * fill-column: 78
 * End:
 */
