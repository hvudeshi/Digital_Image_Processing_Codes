% Author: Hardik Udeshi
% Roll no: 201501113
% Description: Face recognition on images

clc;
clear all;
close all;

%Taking the folder
myFolder = 'yalefaces';
filePattern = fullfile(myFolder, 'sub*');
jpegfile = dir(filePattern);

no_of_images=length(jpegfile);
images = cell(no_of_images,1);

%Forming Images
for i = 1:no_of_images
    basefile = jpegfile(i).name;
    fullfile_new = fullfile(myFolder, basefile);

    images{i} = imread(fullfile_new);
end

[m,n]=size(images{1});
A=zeros(m*n,no_of_images);

%Storing images as Columns
for i=1:no_of_images
    A(:,i)=images{i}(:);
end

%Performing rank and SVD
r=rank(A);
[U,S,V]=svd(A,'econ');

%Image that needs to be nested must be given here
original_image=imread('subject09.sad');
U=U(:,1:r);
imshow(original_image),title('Original image');

%Performing fc*Ui
fc=zeros(no_of_images,r);
for i=1:no_of_images

    f=A(:,i);
    for j=1:r
       fc(i,j)= sum(f.*U(:,j));
    end
end

%Performing g*Ui
G=double(original_image(:));
g=zeros(1,r);
for i=1:r
    g(1,i)=sum(G.*U(:,i));
end

%MeanSquareError Computation
dist=zeros(no_of_images,1);
for i=1:no_of_images
    dist(i)=immse(g,fc(i,:));
    %disp(dist(i));
end

%Finding the minimum Distance
ind=find(dist==min(dist));
figure
imshow(images{ind(1)}),title('Predicted image');