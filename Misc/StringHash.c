/* String Hash
 * Date   : 2018-09-19
 * Author : H.Yin
 * Email  : csustyinhao@gmail.com
*/
#include<stdio.h>
#include<stddef.h>

size_t BKDR_Hash(char *str)
{
    register size_t hash = 0;
    register char *p =str;
    for(hash = 0; *p ; p++)
    {  
        hash = hash * 31 + *p;   //也可以乘以31、131、1313、13131、131313
        // hash = (hash << 5) - hash  + *p;
    }
    return hash;
}

size_t SDBM_Hash(char *str)
{
    register size_t hash = 0;
    register char *p =str;
    for(hash = 0; *p ; p++)
    {  
        hash = hash * 65599 + *p;
        // hash = (hash << 16) + (hash << 6) - hash + *p;
    }
    return hash;
}

size_t RS_Hash(char *str)
{
    register size_t hash = 0, magic = 63689;
    register char *p =str;
    for(hash = 0; *p ; p++)
    {  
        hash = hash * magic + *p;
        magic *= 378551;
    }
    return hash;
}

size_t DEK_Hash(char *str)
{
    register size_t hash = 1315423911;
    register char *p =str;
    if(!*p){
        return 0;
    }
    
    for(; *p ; p++)
    {  
        hash = ((hash << 5) ^ (hash >> 27)) ^ *p;
    }
    return hash;
}

size_t FNV_Hash(char *str)
{
    register size_t hash = 2166136261;
    register char *p =str;
    if(!*p){
        return 0;
    }
    
    for(; *p ; p++)
    {  
        hash *= 16777619;
        hash ^= *p;
    }
    return hash;
}

size_t DJB_Hash(char *str)
{
    register size_t hash = 5381;
    register char *p =str;
    if(!*p){
        return 0;
    }
    
    for(; *p ; p++)
    {  
        hash += (hash << 5) + *p;
    }
    return hash;
}

size_t DJBX33A_Hash(char *str)
{
    register size_t hash = 5381;
    register char *p =str;
    if(!*p){
        return 0;
    }
    
    for(hash = 0; *p ; p++)
    {  
        hash = hash * 33 + *p;
        // hash = ((hash << 5) + hash) + *p;
    }
    return hash;
}

size_t JS_Hash(char *str)
{
    register size_t hash = 1315423911;
    register char *p =str;
    if(!*p){
        return 0;
    }
    
    for(; *p ; p++)
    {  
        hash ^= (hash << 5) + (hash >> 2) + *p;
    }
    return hash;
}
size_t AP_Hash(char *str)
{
    register size_t i = 0, hash = 0;
    register char *p =str;
    if(!*p){
        return 0;
    }
    
    for(i = 0; *p ; p++,i++)
    {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ *p ^ (hash >> 3))
                               : (~((hash << 11) + (*p ^ (hash >> 5))));
    }
    return hash;
}

size_t PJW_Hash(char *str)  
{  
    size_t TotalBits       = sizeof(size_t) * 8;  
    size_t ThreeQuarters   = (TotalBits  * 3) / 4;  
    size_t OneEighth       = TotalBits / 8;  
    size_t HighBits        = ((size_t)-1) << (TotalBits - OneEighth);      
      
    register size_t hash = 0;  
    size_t magic = 0; 
    char *ch = str;
    while (*ch)
    {  
        hash = (hash << OneEighth) + *ch;  
        if ((magic = hash & HighBits) != 0)  
        {  
            hash = ((hash ^ (magic >> ThreeQuarters)) & (~HighBits));  
        }
        ch++;
    }  
    return hash;
}  

size_t ELF_Hash(char *str)  
{  
    size_t TotalBits       = sizeof(size_t) * 8;  
    size_t ThreeQuarters   = (TotalBits  * 3) / 4;  
    size_t OneEighth       = TotalBits / 8;  
    size_t HighBits        = ((size_t)-1) << (TotalBits - OneEighth);
    register size_t hash = 0;  
    size_t magic = 0;  
    char *ch = str;
    while (*ch)  
    {  
        hash = (hash << OneEighth) + *ch;
        if ((magic = hash & HighBits) != 0)  
        {  
            hash ^= (magic >> ThreeQuarters);  
            hash &= ~magic;  
        }
        ch++;
    }  
    return hash;  
}  


int main(){
    char s[100] = {};
    while(1){
        scanf("%s",s);
        if(s[0] == '!'){
            break;
        }
        printf("BKDR_Hash: %u\n", BKDR_Hash(s));
        printf("SDBM_Hash: %u\n", SDBM_Hash(s));
        printf("RS_Hash: %u\n", RS_Hash(s));
        printf("DEK_Hash: %u\n", DEK_Hash(s));
        printf("JS_Hash: %u\n", JS_Hash(s));
        printf("FNV_Hash: %u\n", FNV_Hash(s));
        printf("DJB_Hash: %u\n", DJB_Hash(s));
        printf("DJBX33A_Hash: %u\n", DJBX33A_Hash(s));
        printf("AP_Hash: %u\n", AP_Hash(s));
        printf("PJW_Hash: %u\n", PJW_Hash(s));
        printf("ELF_Hash: %u\n", ELF_Hash(s));
    }
}
