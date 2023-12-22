import os
import numpy as np
from PIL import Image
from struct import pack

def convert_rgb_to_rgb565(r, g, b):
    """ Convert RGB values to RGB565 format. """
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

def convert_rgb_to_bgr565(r, g, b):
    """ Convert RGB values to BGR565 format. """
    return ((b & 0xF8) << 8) | ((g & 0xFC) << 3) | (r >> 3)


def rgb565_to_bytes(rgb565):
    """ Convert RGB565 value to bytes in little endian format. """
    return pack('<H', rgb565)

def process_image(image_path):
    """ Process a single image and return the data in two compression formats. """
    image = Image.open(image_path)
    rgb_image = image.convert('RGB')
    pixels = list(rgb_image.getdata())

    # Method 1: RGB565 for each pixel
    # method1_data = b''.join([rgb565_to_bytes(convert_rgb_to_rgb565(*p)) for p in pixels])

    # Method 1: RGB565 for each pixel
    method1_data = b''.join([rgb565_to_bytes(convert_rgb_to_bgr565(*p)) for p in pixels])

    # Method 2: Compress continuous pixels
    method2_data = b''
    prev_pixel = None
    count = 0

    for pixel in pixels:
        rgb565 = convert_rgb_to_rgb565(*pixel)
        if prev_pixel is None or prev_pixel != rgb565:
            if prev_pixel is not None:
                method2_data += rgb565_to_bytes(prev_pixel) + pack('B', count)
            prev_pixel = rgb565
            count = 1
        else:
            if count < 255:
                count += 1
            else:
                method2_data += rgb565_to_bytes(prev_pixel) + pack('B', count)
                count = 1

    # Add the last pixel
    if prev_pixel is not None:
        method2_data += rgb565_to_bytes(prev_pixel) + pack('B', count)

    return image.width, image.height, method1_data, method2_data

def print_simg_content(data):
    """ Print .simg file content byte by byte as integers. """
    for byte in data:
        print(byte, end=' ')
    print()  # New line at the end

def save_and_print_simg(image_path, output_folder):
    """ Process, save, and print details of an image in .simg format. """
    width, height, method1_data, method2_data = process_image(image_path)

    # Choose the smaller data and set the correct compression_flag as integer
    if len(method1_data) < len(method2_data):
        data = method1_data
        compression_flag = 1
    else:
        data = method2_data
        compression_flag = 2

    # Construct the file header with correct format
    header = pack('<HHB', width, height, compression_flag)

    # Save the .simg file
    output_path = os.path.join(output_folder, os.path.splitext(os.path.basename(image_path))[0] + '.simg')
    with open(output_path, 'wb') as f:
        f.write(header + data)

    # Print size information and chosen compression method
    print(f"이미지 경로     : {image_path}")
    print(f"Method 1 size: {len(method1_data)} bytes")
    print(f"Method 2 size: {len(method2_data)} bytes")
    print(f"Chosen compression method: {compression_flag}")

    # Print .simg content (in bytes) as integers
    print_simg_content(header + data)

    return output_path


def process_folder(folder_path):
    """ Process all images in a folder and save them in /result subfolder. """
    result_folder = os.path.join(folder_path, 'result')
    if not os.path.exists(result_folder):
        os.makedirs(result_folder)

    for filename in os.listdir(folder_path):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp')):
            image_path = os.path.join(folder_path, filename)
            save_and_print_simg(image_path, result_folder)

    return result_folder

folder_path = '/Users/laptop/Desktop/im/'
result_folder = process_folder(folder_path)
print(f"Processed images saved in {result_folder}")
