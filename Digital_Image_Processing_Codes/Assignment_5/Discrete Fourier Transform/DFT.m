%  Author: Hardik Udeshi
%  Description: Take 2 images, find their DFT and swap their amplitudes and save the new images. Write down your observations. This can be done using MATLAB.

clc;
clear all;
close all;

%Taking the images
lenna=im2double(imread('lenna.jpg'));
cameraman=im2double(rgb2gray(imread('cameraman.jpg')));

%Showing the images
figure;
imshow(lenna); 
title('Original Image of Lenna');

figure;
imshow(cameraman); 
title('Original Image of CameraMan');

%FFT of images
fft_1=fft2(lenna);
fft_2=fft2(cameraman);

%Magnitude and Phase of Lenna image
mag_1=abs(fft_1);
phase_1=angle(fft_1);

%Magnitude and Phase of Cameraman Image
mag_2=abs(fft_2);
phase_2=angle(fft_2);

%Reconstruction of Lenna Image
fft_reconst_1=mag_1.*exp(1i*phase_1);
reconst_1=ifft2(fft_reconst_1);

%Reconstruction of Cameraman Image
fft_reconst_2=mag_2.*exp(1i*phase_2);
reconst_2=ifft2(fft_reconst_2);

%Showing the Reconstructed Image
figure;
imshow(reconst_1); 
title('Reconstucted Image of Lenna');

figure;
imshow(reconst_2); 
title('Reconstucted Image of Cameraman');

%Swapping magnitude of Cameraman Image with Lenna Image 
swap_fft_reconstruct_1=mag_2.*exp(1i*phase_1);
swap_reconst_1=ifft2(swap_fft_reconstruct_1);

%Swapping magnitude of Lenna Image with Cameraman Image 
swap_fft_reconst_2=mag_1.*exp(1i*phase_2);
swap_reconst_2=ifft2(swap_fft_reconst_2);

%Showing the swapped Magnitude Image
figure;
imshow(swap_reconst_1); 
title('Reconstucted Image of Lenna after swapping Magnitude');

figure;
imshow(swap_reconst_2); 
title('Reconstucted Image of Cameraman after swapping');
 
