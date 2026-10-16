#include <iostream>
#include<filesystem>
#include <fstream>
using namespace std;
using namespace filesystem;

class file_method{
    long double dir_size =0;
    public:
    void list_dir(){
        dir_size = 0;
        path curr_path = current_path();
        for(auto &entry:directory_iterator(curr_path)){
            
            try{cout<<entry.path().filename()<<endl;
                show_meta(entry.path().string(),10);}
                catch(...){
                    cout<<"some error occured. resuming by skiping that file......"<<endl;
                    cout<<entry.path()<<endl;
                }
            }
            if(dir_size>=1024){
                cout<<"Total size of directory "<<curr_path<<" is "<<dir_size/(1024.0)<<" GB"<<endl;
                
            }
            else cout<<"Total size of directory "<<curr_path<<" is "<<dir_size<<" MB"<<endl;
        };
        void open_folder(string folder){
            if(!exists(current_path()/folder)){ 
                cout<<"Folder not exists"<<endl;
                return;}
                path old_path = current_path();
                if(is_regular_file(current_path()/folder)){
                    cout<<"This is a file so opening its parent folder"<<endl;
                    return;
                }
                current_path(old_path/folder);
            };
            void create_folder(string name){
                if(exists(current_path()/name)){
                    cout<<"This folder already exists"<<endl;
                    return;
                    
                }
                path curr_path = current_path();
                create_directory(curr_path/name);
                if(exists(curr_path/name)){
                    cout<<"Folder created succesfully"<<endl;
                }
            };
            void create_file(string name, string type){
                name = name+"."+type;
                path p = current_path()/name;
                if(exists(p)){
                    cout<<"File already exists"<<endl;
                    return;
                }
                ofstream file((name).c_str());
            };
            void _rename(string old_name,string new_name){
                if(!exists(current_path()/old_name)){
                    cout<<"File does not exists"<<endl;
                    return;
        }
        rename(current_path()/old_name,current_path()/new_name);
    };
    void _delete(string name){
        if(!exists(current_path()/name)){
            cout<<"File does not exists"<<endl;
            return;
        }
        if(is_regular_file(current_path()/name))remove(current_path()/name);
        else if(is_directory(current_path()/name))remove_all(current_path()/name);
    };
    void copy_file(string old_name){
        int i =1;
        if(!exists(current_path()/old_name)){
            cout<<"File does not exists"<<endl;
            return;
        }
        path temp = current_path()/old_name;
        string new_name;
        path p = current_path()/old_name;
        string stem = p.stem().string();
        string extension = p.extension().string();
        string temp1 = stem;
        while(true){
            stem = temp1;
            stem += "_copy(";
            stem += to_string(i);
            stem += ")";
            ifstream file((stem+extension).c_str());
            if(file){
                i++;
            }
            else{
                break;
            }
        }
        stem += extension;
        filesystem::copy_file(temp,stem);
    };
    void copy_folder(string old_name){
        string temp = old_name;
        if(is_regular_file(current_path()/old_name)){
            cout<<"This is not a folder"<<endl;
            return;
        }
        if(!exists(current_path()/old_name)){
            cout<<"Folder not exists"<<endl;
            return;
        }
        string new_name;
        int i=1;
        while(true){
        old_name = temp;
        old_name += "_copy(";
        old_name += to_string(i);
        old_name += ")";
        new_name = old_name;
        if(is_directory(new_name)){
            i++;
        }
        else break;
    }
        filesystem::copy(temp,new_name,copy_options::recursive);
    };
    void move();
    void search(string name){
        for(auto & entry : recursive_directory_iterator(current_path())){
            if(entry.path().filename()==name){
                cout<<"Path: "<<entry.path();
                continue;
            }
        }
    };
    void sort();
    void show_meta(string name,int n){
        path p = current_path()/name;
        string temp;
        double size = 0;
        if(is_regular_file(p)){
        cout<<"File Name: "<<p.filename()<<endl;
         if((file_size(p)/(1024.0*1024.0))>=1024){
                cout<<"size of "<<p.filename()<<"is "<<(file_size(p)/(1024.0*1024.0))/(1024.0)<<" GB"<<endl;
                
            }
        else cout<<"File size: "<<file_size(p)/(1024.0*1024.0)<<" MB"<<endl;
        dir_size += file_size(p)/(1024.0*1024.0);
        cout<<"File type: "<<p.extension()<<endl;
        cout<<endl<<endl;
        return;
    }
        else if(is_directory(p)){
            try{for(auto &entry: recursive_directory_iterator(current_path()/name)){
                if(is_regular_file(entry.path())){
                    size += file_size(entry.path())/(1024.0*1024.0);
                }
            }
            if(size>=1024){
                cout<<"size of "<<p.filename()<<"is "<<size/(1024.0)<<" GB"<<endl;
                
            }
            else cout<<"size of "<<p.filename()<<"is "<<size<<" MB"<<endl;
            dir_size += size;
        }
            catch(...){
                 cout<<"some error occured. resuming by skiping that file......"<<endl;
            }
        }
        else{
            if(n>5) return;
            cout<<"Enter valid file name: ";
            cin>>temp;
            cin.ignore();
            show_meta(temp,n+1);


        }
    };
    void show_menu(){
        char n;
        string name;
        string extension;
        cout<<"a. Current directory"<<endl;
        cout<<"b. List directory"<<endl;
        cout<<"c. Open folder"<<endl;
        cout<<"d. Create folder"<<endl;
        cout<<"e. Create file"<<endl;
        cout<<"f. Rename"<<endl;
        cout<<"g. Delete"<<endl;
        cout<<"h. Copy file"<<endl;
        cout<<"i. Copy folder"<<endl;
        cout<<"j. Move"<<endl;
        cout<<"k. Search"<<endl;
        cout<<"l. Show meta"<<endl;
        cout<<"m. Go to parent folder"<<endl;
        cout<<"Choose(a/b/c/d/e/f/g/h/i/j/k/l/m): ";
            cin>>n;
            cin.ignore();
            cout<<endl<<endl;
            
        switch(n){
            case 'a':
            cout<<current_path();
            cout<<endl<<endl;
            break;
            case 'b':
            list_dir();
            cout<<endl<<endl;
            break;
            case 'c' :
            cout<<"Enter folder name: ";
            getline(cin,name);
            cout<<endl<<endl;
            open_folder(name);
            cout<<endl<<endl;
            break;
            case 'd':
            cout<<"Enter folder name: ";
            getline(cin,name);
            cout<<endl<<endl;
            create_folder(name);
            cout<<endl<<endl;
            break;
            case 'e':
            cout<<"Enter name :";
            cin>>name;
            cin.ignore();
            cout<<"Enter your extension type : ";
            cin>>extension;
            cin.ignore();
            cout<<endl<<endl;
            create_file(name,extension);
            cout<<endl<<endl;
            break;
            case 'f':
            cout<<"Enter file name of file you want to rename: ";
            cin>>name;
            cin.ignore();
            cout<<"Enter new name: ";
            cin>>extension;
            cin.ignore();
            cout<<endl<<endl;
            _rename(name,extension);
            cout<<endl<<endl;
            break;
            case 'g' :
            cout<<"Enter name of the file or folder: ";
            cin>>name;
            cin.ignore();
            cout<<endl<<endl;
            _delete(name);
            cout<<endl<<endl;
            break;
            case 'h' :
            cout<<"Enter name of file: ";
            cin>>name;
            cin.ignore();
            cout<<endl<<endl;
            copy_file(name);
            cout<<endl<<endl;
            break;
            case 'i' :
            cout<<"Enter name of folder: ";
            cin>>name;
            cin.ignore();
            cout<<endl<<endl;
            copy_folder(name);
            cout<<endl<<endl;
            break;
            case 'j' :
            cout<<"Enter name : ";
            cin>>name;
            cin.ignore();
            cout<<endl<<endl;
            cout<<"This feature is currently disabled by admin";
            cout<<endl<<endl;
            break;
            case 'k' :
            cout<<"Enter name: ";
            cin>>name;
            cin.ignore();
            cout<<endl<<endl;
            search(name);
            cout<<endl<<endl;
            break;
            case 'l':
            cout<<"Enter file name: ";
            cin>>name;
            cin.ignore();
            cout<<endl<<endl;
            show_meta(name,0);
            cout<<endl<<endl;
            break;
            case 'm' :
            cout<<endl<<endl;
            current_path(current_path().parent_path());
            cout<<endl<<endl;
            break;
                }
        
    }
};
