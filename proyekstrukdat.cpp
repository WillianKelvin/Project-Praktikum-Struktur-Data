#include <iostream>
#include <malloc.h>
#include <cstring>
#include <iomanip>
#include <fstream>
#define True 1
#define False 0

FILE *in;

using namespace std;
int pilih,No=0,NoHistori=0;
int a=0;

typedef struct typequeue *typeptr;
struct data{
	char nama[30], nama_obat[30][30];
	int jumlah[30],harga[30],jlh;
}info1;

struct simpan{
	char nama[30], nama_obat[30][30];
	int jumlah[30],harga[30],jlh;
}info2;

struct typequeue{
	typeptr kiri;
	typeptr kanan;
	data info1;
	simpan info2;
};



typeptr qdepan,qbelakang, qdepan1, qbelakang1;
typeptr NB;
void buatqueue();
int queuekosong();
void enqueue();
void cetakqueue();
void cetakqueueRiwayat();
void dequeue();
void pop();

	

int no, harga2[30],bnyk2[30];
char nama2[30],nama_obat2 [30][30],namahapus[30],namafile[20],namafile2[20],cekfile;

char kembali;
int main () {
	
	do{
		no=1;
	cout<< "Menu";
	cout<< "\n1. Daftar pembeli";
	cout<< "\n2. Data daftar Pembeli";
	cout<< "\n3. Bayar Obat";
	cout<< "\n4. Riwayat transaksi berhasil";
	cout<< "\n5. Pembatalan pembelian obat";
	cout<< "\n6. Exit";
	cout<< "\nmasukkan menu yang anda pilih : ";cin>>pilih;
	switch (pilih){
		case 1 :
		do{
        cout << "masukkan nama file! data akan tersimpan : "; cin >> namafile;
        in = fopen(namafile,"r");
        if(in){
            cout << "file sudah ada, file sebelumnya akan tertimpa.";
            cout << "tetap dengan nama tersebu? (y/n) "; cin >> cekfile;
        }else{
            cekfile='y';
        }
        fclose(in);
    }while(cekfile=='n'||cekfile=='N');  
        enqueue();
		
		
		break;
		case 2 :
		{
			//if(!queuekosong())
		
				cetakqueue();
			//}
			//else
			//cout << " Tidak ada pembeli!!!" << endl;
		}
	
		break;
		case 3 :
		{
			if(!queuekosong())
			{
				dequeue();
			}
			else
				cout << "tidak ada pembeli!!!" << endl;
			}
		break;
		case 4 :
		cetakqueueRiwayat();
		break;
		case 5 : 
		{
         if(!queuekosong())
             {
                pop();
                    cout << "Tidak jadi membeli!!" << endl;
                }
                else
                    cout << "Belum ada Pembeli!!" << endl;
        }
		break;
		case 6 :
		return 0;
		break;
		}cout << "kembali ke menu <y/n> ? : ";cin>>kembali;
	}while (kembali == 'Y' || kembali == 'y');
}

void buatqueue(){
	qdepan = (typequeue *) malloc (sizeof(typequeue));
	qdepan = NULL;
	qbelakang = qdepan;
	
	qdepan1 = (typequeue *) malloc (sizeof(typequeue));
	qdepan1 = NULL;
	qbelakang1 = qdepan;
}

int queuekosong(){
	if(qdepan==NULL)
	{
		return(True);
	}
	else
		return(False);
}

void enqueue()
{
			while(cekfile=='y'||cekfile=='Y'){
			in = fopen(namafile,"w");
			if (queuekosong())
			{	
				buatqueue();
			}
			
			while ( no ==1)
			{
				
				//if (!queuekosong())
				//{
					//cetakqueue();
				//}
				
				No++;
				fwrite (&No,sizeof(No),1,in);
				cout << "Beli Obat\n";
				cout << "\n==================";
				cout << "\n||==Input data==||";
				cout << "\n==================\n";
				cout << "Nama pelanggan : "; cin.ignore(); cin.getline(nama2,sizeof(nama2));
				NB= (typequeue *) malloc(sizeof (typequeue));
				strcpy(NB->info1.nama,nama2);
				cout << "Masukkan jumlah obat : ";cin>>NB->info1.jlh;
				for (int i=0; i<NB->info1.jlh; i++){
					cout << "obat ke- "<<i+1<<endl;
					cout << "\tnama obat : ";cin.ignore(); cin.getline (nama_obat2[i],sizeof(nama_obat2[i]));
					cout << "\tharga : ";cin>>harga2[i];
					cout << "\tbanyak obat : ";cin>>bnyk2[i];
					strcpy (NB->info1.nama_obat[i],nama_obat2[i]);
					NB->info1.harga[i] = harga2[i];
					NB->info1.jumlah[i] = bnyk2[i];
					if (qdepan == NULL)
					{
						qdepan= NB;
					}
					else
					qbelakang->kanan = NB;
					
					qbelakang = NB;
					qbelakang->kanan = NULL;				
					fwrite(&qdepan->info1,sizeof(qdepan->info1),1,in);
				}
				//a++;
				
				cout << "Tekan 1 untuk menambah pembelian : ";cin>> no;
			}
				fclose(in);
				cekfile='n';
				}
		}


void cetakqueue(){
typeptr bantu;
	int i = 0;
	cout << "\n\t\t\t=====DAFTAR PEMBELI=====" << endl << endl;
	cout<<"masukkan nama file : ";cin>>namafile;
    
		in=fopen(namafile,"r");
		fread(&No,sizeof(No),1,in);
		if(!in){
			cout << "file tidak ditemukan";
		}else if(No==0){
			cout << "file kosong";
		}else{
	cout << setw(4) << "No" << setw(10) << "Nama" << setw(20) << "Nama Obat" << setw(20) << "Harga obat" << setw(20) << "Jumlah obat" << endl;
  	while(fread(&qdepan->info1,sizeof(qdepan->info1),1,in))
    {
        i++;
		int j=0;
		bantu=qdepan;	
        cout << setw(4) << i << setw(13) << bantu->info1.nama; cout<<endl;
        for(j=0; j<bantu->info1.jlh; j++)
			{
				cout << setw(33) << bantu->info1.nama_obat[j]<< setw(17) << bantu->info1.harga[j] << setw(17) << bantu->info1.jumlah[j] <<  endl;
		//j++;
		}
		cout<<"---------------------------------------------------------------------------------"<<endl;
		bantu = bantu->kanan;
  	}
  	cout << "\nJUMLAH ANTRIAN : " << No;
  	cout << endl << endl;
  	fclose(in);
	}
}


void dequeue()
{
	typeptr hapus;

	if (queuekosong())
	{
		cout << "Queue masih kosong!!1";
	}
	else
	{
		hapus = qdepan;
		qdepan = hapus ->kanan;
		
			typeptr NB;
			NB = (typequeue *) malloc (sizeof(typequeue));
			strcpy (NB->info2.nama,hapus->info1.nama);
			NB->info2.jlh=hapus->info1.jlh;
			for (int d=0;d<NB->info2.jlh;d++){
			strcpy (NB->info2.nama_obat[d],hapus->info1.nama_obat[d]);
			NB->info2.harga[d]= hapus->info1.harga[d];
			NB->info2.jumlah[d]= hapus->info1.jumlah[d];
		}
			if (qdepan1 == NULL)
				qdepan1= NB;
			else 
			qbelakang1->kanan = NB;
			
			qbelakang1 = NB;
			qbelakang1->kanan = NULL;
			NoHistori++;
		
		free(hapus);
		No--;
		cout << "PEMBAYARAN SUKSES OLEH " << qbelakang1->info2.nama << endl;
	}
}

void cetakqueueRiwayat()
{
    typeptr bantu;
	int i = 0;
 	bantu = qdepan1;
	cout << "\n\t\t\t=====RIWAYAT PENGIRIMAN=====" << endl;
		cout << setw(4) << "No" << setw(10) << "Nama" << setw(20) << "Nama Obat" << setw(20) << "Harga obat" << setw(20) << "Jumlah obat" << endl;
  	do
    {
        i++;
       int j=0;
        cout << setw(4) << i << setw(13) << bantu->info2.nama; cout<<endl;
			for (j=0; j<bantu->info2.jlh; j++){
			cout << setw(33) << bantu->info2.nama_obat[j]<< setw(17) << bantu->info2.harga [j]<< setw(17) << bantu->info2.jumlah [j] <<  endl;
		 }
		 bantu = bantu->kanan;

  	} while(bantu != NULL && i != NoHistori);
  	cout << "\nJUMLAH ANTRIAN : " << No;
  	cout << endl << endl;
}

void pop (){
	typeptr hapus, bantu;
	if (queuekosong())
	{
		cout << "Antrian Masih Kosong! \n";
	}
	else
	{
		bantu= qdepan;
		hapus = qbelakang;
		 strcpy(namahapus,hapus->info1.nama);
		if ( hapus == qdepan1)
				qdepan1=NULL;
		else
		{
			while (bantu->kanan->kanan!=NULL)
						bantu= bantu->kanan;
					qbelakang=bantu;
					qbelakang->kanan=NULL;
				}
				free(hapus);
			}
			cout<< "\n " <<namahapus;
}
