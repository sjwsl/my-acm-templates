# my-acm-templates
Use Latax to generate your own acm templates  

Enviroment : **Texstudio** in Windows/Mac/Linux

Windows下可能不支持中文路径 若编译报错请使用英文路径  

中文注释乱码请检查代码文件的中文编码方式是否为UTF-8


   
### 1. Clone and Add your own code to any source directory such as `Graph`  
### 2. Make some easy changes in `acm-templates.tex`  
   Just read the file to understand code logic and imitate it  

   `inputmintrd[c++]{Filename}`  is used to add code  

   `includepdf[page={1,2,3}]{Pdfname}` is used to add pdf
### 3. Generate PDF 
   Use `xelatex` to generate PDF   

   Add -shell-escape to the xelatex complilation options in `Preference/Commands`   

   Or use the command line   

   `xelatex -shell-escape acm-templates.tex`   
        

