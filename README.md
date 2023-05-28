# cometconnect
CometConnect is a project built in C language that aims to provide file transfer, chat, video call, and audio call functionalities using an intranet connection and TCP protocol. This README file will guide you through the project setup, usage, and important information.

Features
CometConnect offers the following features:

File transfer: Users can send and receive files over the intranet connection.
Chat: Real-time messaging between multiple users connected to the same intranet network.
Video call: Establish video calls with other users on the intranet.
Audio call: Initiate audio calls and have conversations with other users on the intranet.
Prerequisites
To run CometConnect, ensure you have the following prerequisites installed:

C Compiler: Install a C compiler such as GCC on your system.
Operating System: CometConnect is compatible with Windows, Linux, and macOS.
Setup
Follow these steps to set up CometConnect on your machine:

Clone the repository: Use the following command to clone the repository to your local machine:
copy this code git clone https://github.com/your-username/cometconnect.git
Compile the code: Navigate to the project directory and compile the code using the C compiler. For example:
bash
Copy code
cd cometconnect
gcc -o cometconnect cometconnect.c
Run the application: Execute the compiled code to start the CometConnect application.
bash
Copy code
./cometconnect
Usage
Once you have set up CometConnect, you can use the application to perform various tasks. Follow the on-screen instructions and use the provided commands to utilize different features. Here are the commands for each feature:

File transfer:

To send a file: Use the command /sendfile followed by the path of the file you want to send.
To receive a file: Incoming files will be prompted automatically, follow the instructions on the screen to accept or reject the file.
Chat:

Enter text messages and press Enter to send them to other connected users.
Received messages from other users will be displayed on your screen.
Video call:

Start a video call: Use the command /startvideo to initiate a video call.
Join a video call: Enter the command /joinvideo to join an ongoing video call.
Audio call:

Start an audio call: Use the command /startaudio to initiate an audio call.
Join an audio call: Enter the command /joinaudio to join an ongoing audio call.
Note: For video and audio calls, ensure that your machine has a functioning camera and microphone.

Limitations
CometConnect has a few limitations you should be aware of:

Intranet connection: The application requires an active intranet connection to establish communication between users. It does not support communication over the internet.

Limited scalability: CometConnect is designed for small-scale usage within a local network. It may not perform optimally when used in large-scale deployments.

Basic interface: The application provides a simple command-line interface without any graphical elements.

Security considerations: CometConnect does not implement advanced encryption or authentication mechanisms. It is advisable to use the application within a trusted network environment.

Contributing
We welcome contributions to CometConnect. If you encounter any issues or have ideas for enhancements, please submit them via the project's issue tracker on GitHub. You can also fork the repository, make changes, and create a pull request with your proposed improvements.

License
CometConnect is not Licensed. Feel free to use, modify, and distribute

