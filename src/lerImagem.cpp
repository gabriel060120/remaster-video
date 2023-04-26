#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "upscale.h"


int main(int argc, char* argv[]){
    cv::VideoCapture video;
    video.open("./../o_tumulo_dos_vagalumes.mp4");
    char folder_path_old_frames[] = "./old_frames";
    char folder_path_new_frames[] = "./new_frames";
    
    if(!video.isOpened())
    {
        printf("\nNao conseguimos abrir o arquivo");
        return -1;
    }
    printf("\nArquivo aberto...");
    
    int result_create_folder_old_frames =  mkdir(folder_path_old_frames, S_IRUSR | S_IWUSR | S_IXUSR);
    if(result_create_folder_old_frames != 0)
    {
        printf("\nNao conseguimos criar a pasta");
    } else {
        printf("\nPasta old_frames criada...\n");
    }
    
    int result_create_folder_new_frames =  mkdir(folder_path_new_frames, S_IRUSR | S_IWUSR | S_IXUSR);
    if(result_create_folder_new_frames != 0)
    {
        printf("\nNao conseguimos criar a pasta");
    } else {
        printf("\nPasta new_frames criada...\n");
    }


    cv::Mat frame;
    int frame_number = 0;

    PyObject *module = python_initialize("upscalling.upscalling");
    if (!module) {
        return EXIT_FAILURE;
    }
    while (video.read(frame) && frame_number <10)
    {
        //char frame_file_name[1000000000000];
        //sprintf(frame_file_name, "%d", frame_number);
        //strcat(frame_file_name, ".jpg");

        //char frame_file_path[1000000000000];
        //strcat(frame_file_path, frame_file_name);
        std::string path;

        std::string file_name = "./old_frames/" + std::to_string(frame_number) + ".jpg";
        bool success = cv::imwrite(file_name, frame);
        if(success)
        {
            printf("\nImagem %d salva...", frame_number);
        }
        else
        {
            printf("\n Falha imagem %d!", frame_number);
        }
        frame_number++;
    }

    printf("\n\n");
    for(int i = 0; i < frame_number; i++) {
    std::string file_name = "./../old_frames/" + std::to_string(i) + ".jpg";
    std::string file_name_2 = "./../new_frames/" + std::to_string(i);
    call_from_python(module, "upscalling", file_name.c_str(), file_name_2.c_str());
    printf("Nova Imagem %d processada...\n", i);
    python_finalize();
    }
}
