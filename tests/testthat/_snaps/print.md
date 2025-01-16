# printing works

    Code
      d
    Output
      A c3d object with
      - 55 data points and 340 frames
      - 1.70 s measurement duration (200 fps)
      - 69 analog channels (2000 fps)
      - 2 force platforms with 3400 frames

# prints no force platform data if no data is available

    Code
      d_nof
    Output
      A c3d object with
      - 55 data points and 340 frames
      - 1.70 s measurement duration (200 fps)
      - 69 analog channels (2000 fps)

# prints that force platforms have different number of frames

    Code
      d_drate
    Output
      A c3d object with
      - 55 data points and 340 frames
      - 1.70 s measurement duration (200 fps)
      - 69 analog channels (2000 fps)
      - 2 force platforms with 6800/3400 frames

