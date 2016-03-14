# Adaptive Multimedia Streaming Simulator Framework for ns-3

This repository contains sources for AMuSt-ns3 (Adaptive Multimedia Streaming for ns-3) and is currently work in progress.

Related repositories
 * [AMuSt-libdash](https://github.com/ChristianKreuzberger/AMuSt-libdash) - an extended version of bitmovin's libdash library
 * [AMuSt-ndnSIM](https://github.com/ChristianKreuzberger/AMuSt-ndnSIM) - a modified version of Named Data Networking Simulator (ndnSIM) for AMuSt

## ns-3-dev Readme
The original readme of the ns-3 dev repository can be found [here](https://github.com/ChristianKreuzberger/AMuSt-ns3/blob/master/README).

## Citation
We are currently working on a technical report/paper. For now, you can cite it by using the following text:

Christian Kreuzberger, Daniel Posch, Hermann Hellwagner "AMuSt Framework - Adaptive Multimedia Streaming Simulation Framework for ns-3 and ndnSIM", https://github.com/ChristianKreuzberger/AMust-Simulator/

Bibtex:
```
@misc{kreuzberger2016amust,
  title={AMuSt Framework - Adaptive Multimedia Streaming Simulation Framework for ns-3 and ndnSIM},
  author={Kreuzberger, Christian and Posch, Daniel and Hellwagner, Hermann},
  journal={https://github.com/ChristianKreuzberger/amust-simulator},
  year={2016}
}
```


## Changes to ns-3 code
The following changes were necessary to the ns-3 code:

 * added string_ends_with, zlib_compress_string, zlib_decompress_string in **src/core/model/string.{h,cc}
 * added several http-related applications in src/applications/model/
 * added several helpers in src/applications/model/
 * added those apps and helpers to wscript in src/applications/
 * added zlib compile things to ...
 * added libdash (AMuSt-libdash) compile things to ...


## Licencing
Insert Open Source Licencing Info here (TODO) 


## Acknowledgements
This work was partially funded by the Austrian Science Fund (FWF) under the CHIST-ERA project [CONCERT](http://www.concert-project.org/) 
(A Context-Adaptive Content Ecosystem Under Uncertainty), project number I1402.

