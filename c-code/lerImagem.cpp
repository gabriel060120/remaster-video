#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    cv::VideoCapture video;
    video.open("./../o_tumulo_dos_vagalumes.mp4");
    char folder_path[] = "./../old_frames";
    
    if(!video.isOpened())
    {
        printf("\nNao conseguimos abrir o arquivo");
        return -1;
    }
    printf("\nArquivo aberto...");
    
    int result_create_folder =  mkdir(folder_path, S_IRUSR | S_IWUSR | S_IXUSR);
    if(result_create_folder != 0)
    {
        printf("\nNao conseguimos criar a pasta");
    }
    printf("\nPasta criada...\n");
    
    cv::Mat frame;
    int frame_number = 0;

    while (video.read(frame) && frame_number <10)
    {
        //char frame_file_name[1000000000000];
        //sprintf(frame_file_name, "%d", frame_number);
        //strcat(frame_file_name, ".jpg");
//
        //char frame_file_path[1000000000000];
        //strcat(frame_file_path, frame_file_name);
        std::string path;

        std::string file_name = "./../old_frames/" + std::to_string(frame_number) + ".jpg";
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
    
}