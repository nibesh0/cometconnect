# CometConnect
[video link](https://drive.google.com/drive/folders/1K-3gOTwGNQXIot2M5lZn6QccNHQ-eTnn)

CometConnect is a secure and fast peer-to-peer (P2P) communication project designed for Linux. It utilizes PortAudio, OpenCV, and PThreads to enable efficient and reliable communication between peers.

## Description

CometConnect is a robust P2P communication solution that ensures secure and seamless data transfer. Built specifically for Linux, this project leverages PortAudio for audio processing, OpenCV for video processing, and PThreads for multi-threading capabilities. The aim is to provide real-time communication with low latency and powerfull and fast file sharing, while prioritizing data privacy and security.

## Features

- Secure P2P Communication: CometConnect facilitates secure communication between peers, ensuring that data remains confidential and protected.
- Real-time Audio and Video: Enjoy real-time audio and video streaming capabilities for an immersive communication experience.
- Share file with maximum speed possible.
- Low Latency: CometConnect focuses on minimizing latency to deliver fast and responsive communication.
- Multi-threading Support: The integration of PThreads allows for efficient utilization of system resources and enhances overall application performance.
- Linux Compatibility: Developed specifically for Linux, CometConnect ensures seamless integration and optimal performance on the platform.

## Installation

To use CometConnect, follow these steps:

1. Clone the repository:
```bash
git clone https://github.com/nibesh0/cometconnect.git
```
2. Install required dependencies:
```bash
sudo apt-get update
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
```
3. Install PortAudio:
```bash
sudo apt-get install portaudio19-dev
```
4. Install OpenCV:
```bash
sudo apt-get install libopencv-dev
```

## Usage

To use CometConnect , follow these steps:

1. install the required library.
2. To compile the server use the following command
```bash
g++ mainserver.c -o server `pkg-config --libs --cflags opencv4` -pthread -lportaudio
```
3. To compile the client use the following command
```bash
g++ mainclient.c -o client `pkg-config --libs --cflags opencv4` -pthread -lportaudio
```
4. Give executable permission to client and server .the server should do the first move.
```bash
chmod +x client
chmod +x server
```
5. Usage of server and client
```bash 
./server <ip of server>
```
```bash
./client <ip of server>
```
6. Establish a P2P connection between peers using the provided functions.
7. Terminate the communication and release any allocated resources using the provided cleanup functions.



## Contributing

Contributions to CometConnect are welcome! To contribute, follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature`
3. Make your changes and commit them: `git commit -m 'Add your feature'`
4. Push the changes to your forked repository: `git push origin feature/your-feature`
5. Open a pull request on the main repository.

Please ensure that your contributions align with the project's coding standards and guidelines.

## License

CometConnect is licensed under the [MIT License](https://opensource.org/licenses/MIT).

## Support

For any questions, issues, or support related to CometConnect, please refer to the [issue tracker](https://github.com/nibesh0/cometconnect/issues) on GitHub.

## Roadmap

The future roadmap for CometConnect includes the following:

- Implementing end-to-end encryption for enhanced security.
- Adding a better audio streaming.
- Enhancing the user interface and experience.
- Optimizing performance and reducing latency.

Your feedback are invaluable in shaping the future development of CometConnect.

## Authors

CometConnect is developed and maintained by the following authors:

- [Devanshu Dagi](https://github.com/DevanshuDangi)
- [Nibesh sahu](https://github.com/nibesh0)
- [Aditya sharma](https://github.com/)

## Credits

CometConnect is developed as a capstone project. We would like to thank the following individuals and resources for their contributions:
- [PortAudio](https://www.portaudio.com): Library for audio processing.
- [OpenCV](https://opencv.org): Library for computer vision and video processing.
- [PThreads](https://en.wikipedia.org/wiki/POSIX_Threads): Library for multi-threading support.

Thank you for using CometConnect!


