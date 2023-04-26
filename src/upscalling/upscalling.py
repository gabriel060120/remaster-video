from skimage import io, transform
import os

def upscalling(path, nome):
    img = io.imread(path, plugin='pil', plugin_args={'mode': 'r'})

    scale_factor = 3
    new_size = (img.shape[0]*scale_factor, img.shape[1]*scale_factor)
    resized_img = transform.resize(img, new_size, mode='reflect')
    
    folder_name = 'output'
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
    
    io.imsave(os.path.join(folder_name, f'{nome}.jpg'), resized_img)

    return 0
