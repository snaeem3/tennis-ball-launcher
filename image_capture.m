blobAnalyzer = vision.BlobAnalysis('BoundingBoxOutputPort',false,'MinimumBlobArea',50);

%s = serial('/dev/tty.usbmodemM4321001');
%set(s,'BaudRate',9600);
%fopen(s);

%cam = webcam('USB2.0 PC CAMERA #2')
%cam = webcam('FaceTime HD Camera')

img = snapshot(cam);

[R, C, ~] = size(img);
sign = '0';
flushinput(s)
%{
while 1
    for i = ['1', '2', '3', '4', '5', '6', '7', '8', '9']
        fprintf(s,i);
        pause(.5)
        i
        %a = fscanf(s)
        pause(.5);
    end
end
%}


while 1

    img = snapshot(cam);
    %imshow(img)
    %pause(.1)
    
    [~, img] = find_sprite(img);
    %imshow(img)
    %pause(.1)
    
    gray = rgb2gray(img);
    %imshow(gray)
    %pause(.1)
    
    gray = gray > 50;
    %imshow(gray)
    %pause(.1)
    
    gray = bwareaopen(gray,200);
    %imshow(gray)
    %pause(.1)
    
    [area,centroid] = step(blobAnalyzer,gray);
    [~, i] = max(area);
    center = centroid(i, :);
    try
        y_error = (center(2) - R/2)/R;
        x_error = (center(1) - C/2)/C;
        
    
        ye_str = sprintf('%.2f',abs(y_error));
        if (y_error<0)
            sign = '1';
        else
            sign = '0';
        end
    
        ye_packet = [sign ye_str(3) ye_str(4)]
        for c = ye_packet            
            fprintf(s,c);
            pause(.01);
            %fscanf(s)
            %pause(.01);
        end
        
    pause(.01);
    end
        
        

end