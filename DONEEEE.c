// by Muhammad Naufal Rafiantp
// Input maksimal 1 digit

#define UKURAN 50 // Ukuran Stack
#include <ctype.h> //  berisi operator-operator untuk pengolahan karakter.
#include <stdio.h> // header yang berisi definisi makro, konstanta, dan deklarasi fungsi dan jenis yang digunakan untukberbagai standard input dan output operasi
#include <math.h>// header untuk memanggil fungsi matematika

// ----------------------------------------------------------------------------

// Deklarasi Variabel Universal
char s[UKURAN];
int top = -1;

// ----------------------------------------------------------------------------

// Fungsi untuk Menghilangkan spasi
void hilangkanSpasi(char* source)
{
    char* i = source;
    char* j = source;
    while(*j != 0)
    {
        *i = *j++;
        if(*i != ' ') // jika terdapat spasi berarti bernilai nol atau tidak dianggap
        i++;
    }
    *i = 0;
}

/* Fungsi untuk memasukkan karakter ke dalam stack */
void masuk(char elemen)
{
    s[++top] = elemen;
}

/* Fungsi untuk Mengeluarkan karakter dari stack */
char keluar()
{
    return (s[top--]);
}

/* Fungsi untuk memprioritaskan operator */
int prioritas(char elemen)
{
    switch (elemen)
    {
        case '#':
            return 0;
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
    }
}


// Fungsi untuk mengubah dari ekspresi infix menuju ekspresi postfix 
// Notasi infix = dari ( A + B ) * ( A - B) 
// Notasi Postfix =  A B + A B - *
// -----------------------------------------------------------------
void ubah_ke_postfix(char *infix, char *postfix)
{
    char ch, elemen;
    int i = 0, k = 0;

    hilangkanSpasi(infix); // Menghilangkan spasi pada input
    masuk('#');

    while ((ch = infix[i++]) != '\n')  // Ketika Input belum sama dienter maka input terus berjalan
    {
        if (ch == '(')                   // Jika terdapat '(' maka dalam input maka '(' akan didorong menuju stack
            masuk(ch);
        else if (isalnum(ch))           // isalnum adalah fungsi untuk memeriksa apakah argument adalah alfanumerik atau bukan
            postfix[k++] = ch;              
        else if (ch == ')')             // Jika  kurung buka '(' dan kurung tutup ')' sudah bertemu maka keduannya akan akan di keluarkan dari stack
        {                               // tanda kurung '()' tidak akan tercetak di notasi postfix
            while (s[top] != '(')
                postfix[k++] = keluar();    // ketika top dari stack bukan '(' maka akan karakter tidak akan masuk stack
            elemen = keluar(); 
        }
        else { 
                while (prioritas(s[top]) >= prioritas(ch))      //ketika tingkatan operator lebih tinggi dari operator lainnya maka opertaor tertinggi akan terletak di paling kiri
                postfix[k++] = keluar();
                masuk(ch);
            }
    }

    while (s[top] != '#') /* Mengosongkan Stack hingga bersih */
        postfix[k++] = keluar();
        postfix[k] = 0; /* Menjadikan postfix sebagai string  */
}

/*
* Fungsi Untuk Mengevaluasi Postfix 
*/
int hitung(char *postfix)
{
    char ch;
    int i = 0, op1, op2;
    while((ch = postfix[i++]) != 0)
    {
        if(isdigit(ch)) // isdigit adalah fungsi untuk memeriksa apakah karakater adalah numerik (0 - 9)
            masuk(ch-'0');  // Kika argumen berupa angka maka program akan mendorong angka menuju stack
        else
        { // ketika bertemu operator maka angka akan dikeluarkan dari stack untuk dilakukan operasi
         op2 = keluar();
         op1 = keluar();
         switch(ch)
         {
            case '+' :
                masuk(op1+op2);
                break;
            case '-' :
                masuk(op1-op2);
                break;
             case '^' :
                masuk(pow(op1,op2));
                break;
            case '*' :
                masuk(op1*op2);
                break;
            case '/' :
                masuk(op1/op2);
                break;
            default:
                puts("Operator Tidak Valid");
         }
        }
    }
    return s[top];
}

/* Program Utama */
void main()
{
    char infix[50], postfix[50];

    //Syntax Input Dari USER
    printf("Masukkan Ekspresi Matematika: \n");
    fgets(infix, 100, stdin);   // Syntax fgets lebih dinamis dibanding dari scanf

    ubah_ke_postfix(infix, postfix); // Setelah Mendapatkan Input lalu Memanggil Fungsi Infix untuk dijadikan postfix
    printf("Hasil: %d", hitung(postfix)); //lalu mencetaknya setelah mengevaluasi postfix
}
