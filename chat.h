#pragma once

#include "sha1.h"
//#include "test.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
    public:
        Chat();
        ~Chat(){
       	    for(int i=0;i<mem_size;i++){
       	    	delete data[i].pass_sha1_hash;
			}
        	delete data;
		}
        void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
        bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);
        
        //friend void test(Chat& c);
    private:
        enum enPairStatus {
            free,
            engaged,
            deleted
        };    	
    	
        struct AuthData {
            AuthData():                 
                pass_sha1_hash(nullptr), status(enPairStatus::free)
			{
                login[0]=(char)0;
                
            }
            ~AuthData() {
                /*if(pass_sha1_hash != 0 )
                    delete [] pass_sha1_hash;*/
            }
            AuthData(char _login[LOGINLENGTH], uint* sh1) {
                strcpy(login, _login);
                pass_sha1_hash = sh1;
                status=enPairStatus::engaged;
            }
            AuthData& operator = (const AuthData& other) {
                strcpy(login, other.login);
                
                if(pass_sha1_hash != 0)
                    delete [] pass_sha1_hash;
                pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
                
                memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
                
                status=other.status;
                
                return *this;
            }           
            char login[LOGINLENGTH];
            uint* pass_sha1_hash;
            enPairStatus status;
		
        };
   
    AuthData* data;
    int mem_size;
    int count;		
	
public:	
	void add(char* fr_name, uint* pass_sha1_hash) {
    	int index = -1, i = 0;
	    // ����� ����� �� ���� i �� 0 �� ������� �������
    	for(;i < mem_size; i++) {
        	index = hash_func(fr_name, i);
	        if(data[index].status == enPairStatus::free) { 
    	        // ������� ������ ������, �������� ��
        	    break;
	        }
    	}
    	if(i >= mem_size){ // ��� ���������, ��� �����
    		resize();
 			index = -1, i = 0;
	    	// ����� ����� �� ���� i �� 0 �� ������� �������
    		for(;i < mem_size; i++) {
	        	index = hash_func(fr_name, i);
		        if(data[index].status == enPairStatus::free) { 
    		        // ������� ������ ������, �������� ��
        		    break;
	        	}
    		}    	
    	}
    
	    // ������ � ��������� ������ ����
    	data[index] = AuthData(fr_name, pass_sha1_hash);
    	count++;
	}
	int hash_func(char* fr_name, int offset) {
    	// ��������� ������
	    int sum = 0, i = 0;
    	for(; i<LOGINLENGTH; i++) {
        	sum += fr_name[i];
	    }
    	// ������������ �����
    	return (sum % mem_size + offset*offset) % mem_size; 
	}
	
	uint* find(char* fr_name) {
	    int index = -1, i = 0;
    	for(;i < mem_size; i++) {
        	index = hash_func(fr_name, i);
	        if(data[index].status == enPairStatus::engaged && strcmp(data[index].login,fr_name)==0 ) { 
        	    return data[index].pass_sha1_hash;
        	}
    	}   
	    return nullptr;
	}	
	
	

	void resize() {
    	// �� �������� �������� ����� resize() � ������ �����
	    // ������ ������ add, � ����� �������� ������� � ����������� ������
    	// ��� ���
	    int oldSize = mem_size;    
    
	    mem_size *= 2;  // ����������� ������ � ��� ����  
    	count = 0; // �������� ���������� ���������

    	AuthData* array0=data;
    
    	data = new AuthData [mem_size];
    
		for(int i =0; i<oldSize; i++) {
	        // ���������� ��� ������ �������
    	    if(array0[i].status == enPairStatus::engaged) {
        	    // ������������� ���� � ��������� � ����� ������
            	add(array0[i].login, array0[i].pass_sha1_hash);
	            // ���������� ��� ���� � ������
    	    }
	    }
	    delete array0;
	}	
		                
};//
