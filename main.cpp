#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // Define folder names
    const std::string pictureFolder = "/home/t/Downloads/pictures";
    const std::string videoFolder = "/home/t/Downloads/videos";
    const std::string documentFolder = "/home/t/Downloads/documents";
    const std::string otherFolder = "/home/t/Downloads/others";
    const std::string downloadFolder = "/home/t/Downloads/";

    // Create folders
    fs::create_directory(pictureFolder);
    fs::create_directory(videoFolder);
    fs::create_directory(documentFolder);
    fs::create_directory(otherFolder);

    // File moving operations
    for (const auto& dirEntry : fs::directory_iterator(downloadFolder)) {
        if (fs::is_regular_file(dirEntry)) {
            const std::string filename = dirEntry.path().filename().string();
            const std::string extension = dirEntry.path().extension().string();

            // Move to appropriate folder
            std::string destinationFolder = otherFolder; // Default to 'others'
            if (extension == ".jpg" || extension == ".png") {
                destinationFolder = pictureFolder;
            } else if (extension == ".mp4" || extension == ".avi") {
                destinationFolder = videoFolder;
            } else if (extension == ".doc" || extension == ".docx" || extension == ".txt" || extension == ".xls" || extension == ".xlsx" || extension == ".pdf") {
                destinationFolder = documentFolder;
            }

            // Move the file
            fs::rename(dirEntry.path(), destinationFolder + "/" + filename);
        }
    }

    std::cout << "File moving operation completed." << std::endl;

    return 0;
}
