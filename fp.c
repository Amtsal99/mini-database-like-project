#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
typedef long long ll;
void home();
void query();
void tambah();
void query_m();
void query_tm();
void query_p();
void query_bph();
void query_tm_id();
void query_tm_tgl();
void query_tm_mp();
void query_m_nrp();
void query_m_nama();
void query_m_notelp();
void query_p_id();
void query_p_nama();
void query_p_tgl();
void query_bph_nrp();
void query_bph_nama();
void query_bph_jabatan();
void query_bph_notelp();
void read_file();
void hapus();
void hapus_tm();
void hapus_m();
void hapus_p();
void update();
void update_tm();
void update_m();
void update_p();
void keluar();
void log_in();
int alr_read=0;
ll nrp_login;
int isNull_tm=1,isNull_m=1,isNull_p=1;

struct tanggal{
    int hari;
    int bulan;
    int tahun;
};
struct mahasiswa{
    ll nrp;
    char nama[50];
    ll notelp;
	struct mahasiswa *next;
	struct mahasiswa *prev;
};
struct transaksi_masuk{
    int id;
    struct tanggal tgl;
    char metode_pembayaran[15];
    int jumlah;
    ll nrp_mhs;
    ll nrp_bph;
	struct transaksi_masuk *next;
	struct transaksi_masuk *prev;
};
struct Bph{
	ll nrp;
	char nama[50];
	ll notelp;
	char jabatan[50];
	char pw[50];
	struct Bph *next;
	struct Bph *prev;
};
struct produk{
    int id;
    char nama[50];
    int harga;
    struct tanggal tgl;
    int id_tm;
	struct produk *next;
	struct produk *prev;
};
struct Bph *head=NULL;
struct Bph *tail=NULL;
struct transaksi_masuk *tmhead=NULL;
struct transaksi_masuk *tmtail=NULL;
struct mahasiswa *mhead=NULL;
struct mahasiswa *mtail=NULL;
struct produk *phead=NULL;
struct produk *ptail=NULL;

int main(){ 
    log_in();
    return 0;
}
void log_in(){
	if(!alr_read){
		read_file();
		alr_read=1;	
	}
	while(1){
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("LOG IN : \n");
		int flag=0;
		ll tp_nrp;
		char tp_pw[50];
		printf("Masukkan NRP 		: ");scanf("%lld",&tp_nrp);
		printf("Masukkan password 	: ");scanf("%s",tp_pw);
		struct Bph *cur=head;
		while(cur!=NULL){
			if(cur->nrp==tp_nrp&&(strcmp(cur->pw,tp_pw)==0)){
				flag =1; 
				nrp_login=cur->nrp;
				break;
			}
			else cur=cur->next;
		}
		if(flag){
			printf("Login Berhasil !\n");
			system("pause");
			break;
		}
		printf("Login gagal, data tidak ditemukan \n");
		system("pause");
	}
	home();
}
void read_file(){
	FILE *mfile=fopen("mhs.txt","r+");
	FILE *tmfile=fopen("tm.txt","r+");
	FILE *pfile=fopen("p.txt","r+");
	FILE *file = fopen("bph.txt","r");
	/*int id;
    struct tanggal tgl;
    char metode_pembayaran;
    int jumlah;
    ll nrp_mhs;
    ll nrp_bph;
	struct transaksi_masuk *next;
	struct transaksi_masuk *prev;*/
	fseek(tmfile,0,SEEK_END);
	if(ftell(tmfile)!=0){
		fseek(tmfile,0,SEEK_SET);
		isNull_tm=0;
		struct transaksi_masuk *tmtp=(struct transaksi_masuk *)malloc(sizeof(struct transaksi_masuk));
		fscanf(tmfile,"Id       : %d\nTanggal  : %d %d %d\nMetode   : %s\nJumlah   : %d\nNRP_Mhs  : %lld\nNRP_BPH  : %lld\n",&(tmtp->id),&((tmtp->tgl).hari),&((tmtp->tgl).bulan),&((tmtp->tgl).tahun),tmtp->metode_pembayaran,&(tmtp->jumlah),&(tmtp->nrp_mhs),&(tmtp->nrp_bph));
		tmtp->next=NULL;
		tmtp->prev=NULL;
		tmhead=tmtp;
		tmtail=tmtp;
		int temp_id,temp_tgl_hari,temp_tgl_bulan,temp_tgl_tahun,temp_jumlah;
		char temp_mp[15];
		ll temp_nrp_mhs,temp_nrp_bph;
		//di bawah ini untuk stream input dari file ke program//
		while(fscanf(tmfile,"Id       : %d\nTanggal  : %d %d %d\nMetode   : %s\nJumlah   : %d\nNRP_Mhs  : %lld\nNRP_BPH  : %lld\n",&temp_id,&temp_tgl_hari,&temp_tgl_bulan,&temp_tgl_tahun,temp_mp,&temp_jumlah,&temp_nrp_mhs,&temp_nrp_bph)==8){
			struct transaksi_masuk *temp=(struct transaksi_masuk*)malloc(sizeof(struct transaksi_masuk)) ;
			printf("Di bagian read tm yang salah\n");
			temp->id=temp_id;
			(temp->tgl).hari=temp_tgl_hari;
			(temp->tgl).bulan=temp_tgl_bulan;
			(temp->tgl).tahun=temp_tgl_tahun;
			strcpy(temp->metode_pembayaran,temp_mp);
			temp->nrp_mhs=temp_nrp_mhs;
			temp->nrp_bph=temp_nrp_bph;
			temp->prev=tmtail;
			temp->next=NULL;
			tmtail->next=temp;
			tmtail=temp;
		}
	}
	
	/*struct mahasiswa{
    ll nrp;
    char nama[50];
    ll notelp;
	struct mahasiswa *next;
	struct mahasiswa *prev;
	};*/
	fseek(mfile,0,SEEK_END);
	if(ftell(mfile)!=0){
		fseek(mfile,0,SEEK_SET);
		isNull_m=0;
		struct mahasiswa *mtp=(struct mahasiswa*)malloc(sizeof(struct mahasiswa));
		fscanf(mfile,"NRP      : %lld\nNama     : %s\nNo. Telp : %lld\n",&(mtp->nrp),mtp->nama,&(mtp->notelp));
		mtp->next=NULL;
		mtp->prev=NULL;
		mhead=mtp;
		mtail=mtp;
		
		char temp_mhs_nama[50];
		ll temp_mhs_notelp,temp_mhs_nrp;
		//di bawah ini untuk stream input dari file ke program struct mahasiswa//
		while(fscanf(mfile,"NRP      : %lld\nNama     : %s\nNo. Telp : %lld\n",&temp_mhs_nrp,temp_mhs_nama,&temp_mhs_notelp)==3){
			struct mahasiswa *mtemp=(struct mahasiswa*)malloc(sizeof(struct mahasiswa)) ;
			printf("Bagian read file mahasiswa juga salah ! \n");
			mtemp->nrp=temp_mhs_nrp;
			strcpy(mtemp->nama,temp_mhs_nama);
			mtemp->notelp=temp_mhs_notelp;
			mtemp->prev=mtail;
			mtemp->next=NULL;
			mtail->next=mtemp;
			mtail=mtemp;
		}
	}
	
	// di bawah ini digunakan untuk memasukkan data pada produk//
	/*struct produk{
    int id;
    char nama[50];
    int harga;
    struct tanggal tgl;
    int id_tm;
	struct produk *next;
	struct produk *prev;
	};*/
	struct produk *ptp=(struct produk*)malloc(sizeof(struct produk));
	fseek(pfile,0,SEEK_END);
	if(ftell(pfile)!=0){
		fseek(pfile,0,SEEK_SET);
		isNull_p=0;
		fscanf(pfile,"Id       : %d\nNama     : %s\nHarga    : %d\nTanggal  : %d %d %d\nId_TM    : %d\n",&(ptp->id),ptp->nama,&(ptp->harga),&((ptp->tgl).hari),&((ptp->tgl).bulan),&((ptp->tgl).tahun),&(ptp->id_tm));
		ptp->next=NULL;
		ptp->prev=NULL;
		phead=ptp;
		ptail=ptp;
		
		char temp_p_nama[50];
		int temp_p_id,temp_p_tgl_hari,temp_p_tgl_bulan,temp_p_tgl_tahun,temp_p_id_tm,temp_p_harga;
		//di bawah ini untuk stream input dari file ke program struct mahasiswa//
		while(fscanf(pfile,"Id       : %d\nNama     : %s\nHarga    : %d\nTanggal  : %d %d %d\nId_TM    : %d\n",&temp_p_id,temp_p_nama,&temp_p_harga,&temp_p_tgl_hari,&temp_p_tgl_bulan,&temp_p_tgl_tahun,&temp_p_id_tm)==7){
			struct produk *ptemp=(struct produk*)malloc(sizeof(struct produk)) ;
			printf("Bagian read file buat produk juga salah bro\n");
			ptemp->id=temp_p_id;
			strcpy(ptemp->nama,temp_p_nama);
			ptemp->harga=temp_p_harga;
			(ptemp->tgl).hari=temp_p_tgl_hari;
			(ptemp->tgl).bulan=temp_p_tgl_bulan;
			(ptemp->tgl).tahun=temp_p_tgl_tahun;
			ptemp->id_tm=temp_p_id_tm;
			ptemp->prev=ptail;
			ptemp->next=NULL;
			ptail->next=ptemp;
			ptail=ptemp;
		}
	}
	struct Bph *tp=(struct Bph *)malloc(sizeof(struct Bph));
	fscanf(file,"NRP      : %lld\nNama     : %s\nNo. Telp : %lld\nJabatan  : %s\nPassword : %s\n",&(tp->nrp),tp->nama,&(tp->notelp),tp->jabatan,tp->pw);
	tp->next=NULL;
	tp->prev=NULL;
	head=tp;
	tail=tp;
	char temp_nama[50],temp_jabatan[50],temp_pw[50];
	ll temp_nrp,temp_notelp;
	//di bawah ini untuk stream input dari file ke program//
	while(fscanf(file,"NRP      : %lld\nNama     : %s\nNo. Telp : %lld\nJabatan  : %s\nPassword : %s\n",&temp_nrp,temp_nama,&temp_notelp,temp_jabatan,temp_pw)==5){
		struct Bph *temp=(struct Bph*)malloc(sizeof(struct Bph)) ;
		temp->nrp=temp_nrp;
		temp->notelp=temp_notelp;
		strcpy(temp->nama,temp_nama);
		strcpy(temp->jabatan,temp_jabatan);
		strcpy(temp->pw,temp_pw);
		temp->prev=tail;
		temp->next=NULL;
		tail->next=temp;
		tail=temp;
	}
	fclose(file);
	fclose(tmfile);
	fclose(mfile);
	fclose(pfile);
}
void home(){
	
    char a;
    int pilih=1;
    while(1){
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		if(pilih==1){
			//system("cls");//
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|      ===>>[  TAMBAH DATA PEMBELIAN  ]<<===      |\n");
    		printf("|           [          QUERY          ]           |\n");
			printf("|           [         UPDATE          ]           |\n");
			printf("|           [         DELETE          ]           |\n");
			printf("|           [          EXIT           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}else if(pilih==2){
			//system("cls");//
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|           [  TAMBAH DATA PEMBELIAN  ]           |\n");
    		printf("|      ===>>[          QUERY          ]<<===      |\n");
			printf("|           [         UPDATE          ]           |\n");
			printf("|           [         DELETE          ]           |\n");
			printf("|           [          EXIT           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
 		}else if(pilih==3){
			//system("cls");//
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|           [  TAMBAH DATA PEMBELIAN  ]           |\n");
    		printf("|           [          QUERY          ]           |\n");
			printf("|      ===>>[         UPDATE          ]<<===      |\n");
			printf("|           [         DELETE          ]           |\n");
			printf("|           [          EXIT           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}
		else if(pilih==4){
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|           [  TAMBAH DATA PEMBELIAN  ]           |\n");
    		printf("|           [          QUERY          ]           |\n");
			printf("|           [         UPDATE          ]           |\n");
			printf("|      ===>>[         DELETE          ]<<===      |\n");
			printf("|           [          EXIT           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}
		else {
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|           [  TAMBAH DATA PEMBELIAN  ]           |\n");
    		printf("|           [          QUERY          ]           |\n");
			printf("|           [         UPDATE          ]           |\n");
			printf("|           [         DELETE          ]           |\n");
			printf("|      ===>>[          EXIT           ]<<===      |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}
		a=getch();
		if(a==72){
			pilih--;
			if(pilih<1){
				pilih=5;
			}
		}else if(a==80){
			pilih++;
			if(pilih>5){
				pilih=1;
			}
		}else if(a==13){
			break;
		}
	}
	if(pilih==3){
		update();
	}
	else if(pilih==1){
		tambah();
	}
	else if(pilih==2){
		query();
	}
	else if(pilih==4){
		hapus();
	}
	else {
		keluar();
	}
	

}

void tambah(){

	while(1){
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("        ===>>[  TAMBAH DATA PEMBELIAN  ]<<===       \n");
		printf("Menambahkan Data Transaksi Masuk\n");

		/*int id;
		struct tanggal tgl;
		char metode_pembayaran;
		int jumlah;
		ll nrp_mhs;
		ll nrp_bph;
		struct transaksi_masuk *next;
		struct transaksi_masuk *prev;*/

		struct transaksi_masuk *tmtp=(struct transaksi_masuk *)malloc(sizeof(struct transaksi_masuk));
		printf("Masukkan Tanggal Transaksi [dd/mm/yy] : ");
		scanf("%d %d %d",&((tmtp->tgl).hari),&((tmtp->tgl).bulan),&((tmtp->tgl).tahun));
		printf("Masukkan Metode Pembayaran            : ");scanf("%s",tmtp->metode_pembayaran);
		printf("Masukkan Jumlah Transaksi             : ");scanf("%d",&(tmtp->jumlah));
		printf("Masukkan NRP Mahasiswa yang Terkait   : ");scanf("%lld",&(tmtp->nrp_mhs));
		tmtp->nrp_bph=nrp_login;
		if(isNull_tm){
			tmtp->id=1;
			tmtp->prev=NULL;
			tmtp->next=NULL;
			tmhead=tmtp;
			tmtail=tmtp;
			isNull_tm=0;
		}
		else{
			tmtp->id=tmtail->id+1;
			tmtp->prev=tmtail;
			tmtp->next=NULL;
			tmtail->next=tmtp;
			tmtail=tmtp;
		}
		printf("Data Transaksi Masuk Berhasil Dimasukkan !\n");
		system("pause");
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("        ===>>[  TAMBAH DATA PEMBELIAN  ]<<===       \n");
		printf("Menambahkan Data Mahasiswa Terkait\n");
		
		/*struct mahasiswa{
		ll nrp;
		char nama[50];
		ll notelp;
		struct mahasiswa *next;
		struct mahasiswa *prev;
		};*/

		struct mahasiswa *mtp=(struct mahasiswa *)malloc(sizeof(struct mahasiswa));
		mtp->nrp=tmtp->nrp_mhs;
		printf("Masukkan Nama Mahasiswa               : ");scanf("%s",mtp->nama);
		printf("Masukkan Nomor Telepon Mahasiswa      : ");scanf("%lld",&(mtp->notelp));
		if(isNull_m){
			mtp->prev=NULL;
			mtp->next=NULL;
			mhead=mtp;
			mtail=mtp;
			isNull_m=0;
		}
		else{
			mtp->prev=mtail;
			mtp->next=NULL;
			mtail->next=mtp;
			mtail=mtp;
		}
		printf("Data Mahasiswa Berhasil Dimasukkan !\n");
		system("pause");
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("        ===>>[  TAMBAH DATA PEMBELIAN  ]<<===       \n");
		printf("Menambahkan Data Produk Terkait\n");
		while(1){
			/*struct produk{
			int id;
			char nama[50];
			int harga;
			struct tanggal tgl;
			int id_tm;
			struct produk *next;
			struct produk *prev;
			};*/
			struct produk *ptp=(struct produk *)malloc(sizeof(struct produk));
			printf("Masukkan Nama Produk                  : ");scanf("%s",ptp->nama);
			printf("Masukkan Harga Produk                 : ");scanf("%d",&(ptp->harga));
			printf("Masukkan Tanggal Diterima [dd/mm/yy]  : ");scanf("%d %d %d",&((ptp->tgl).hari),&((ptp->tgl).bulan),&((ptp->tgl).tahun));
			ptp->id_tm=tmtail->id;
			if(isNull_p){
				ptp->id=1;
				ptp->prev=NULL;
				ptp->next=NULL;
				phead=ptp;
				ptail=ptp;
				isNull_p=0;
			}
			else {
				ptp->id=ptail->id+1;
				ptp->prev=ptail;
				ptp->next=NULL;
				ptail->next=ptp;
				ptail=ptp;
			}

			char ans;
			printf("Apakah Ingin Menambahkan Produk Lagi? [y/n] : ");
			int f=0;
			ans=getchar();
			while(1){
				ans=getchar();
				if(ans!='\n')break;
			}
			if(ans!='y')break;
		}
		char ans2;
		printf("Apakah Ingin Menambahkan Transaksi Masuk Lagi? [y/n] :");
		while(1){
			ans2=getchar();
			if(ans2!='\n')break;
		}
		if(ans2!='y')break;
	}
	home();
	
}

void query(){

	int pilih=1;
	while(1){
		char a;
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("       ===>>[          QUERY          ]<<===        \n");
		if(pilih==1){
			//system("cls");//
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|      ===>>[     TRANSAKSI MASUK     ]<<===      |\n");
    		printf("|           [        MAHASISWA        ]           |\n");
			printf("|           [          PRODUK         ]           |\n");
			printf("|           [           BPH           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}else if(pilih==2){
			//system("cls");//
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|      	    [     TRANSAKSI MASUK     ]           |\n");
    		printf("|      ===>>[        MAHASISWA        ]<<===      |\n");
			printf("|           [          PRODUK         ]           |\n");
			printf("|           [           BPH           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
 		}else if(pilih==3){
			//system("cls");//
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|      	    [     TRANSAKSI MASUK     ]           |\n");
    		printf("|           [        MAHASISWA        ]           |\n");
			printf("|      ===>>[          PRODUK         ]<<===      |\n");
			printf("|           [           BPH           ]           |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}
		else {
			printf("|=================================================|\n");
			printf("|                                                 |\n");
			printf("|           [     TRANSAKSI MASUK     ]           |\n");
    		printf("|           [        MAHASISWA        ]	          |\n");
			printf("|           [          PRODUK         ]           |\n");
			printf("|      ===>>[           BPH           ]<<===      |\n");
			printf("|                                                 |\n");
			printf("|=================================================|\n");
		}
		a=getch();
		if(a==72){
			pilih--;
			if(pilih<1){
				pilih=4;
			}
		}else if(a==80){
			pilih++;
			if(pilih>4){
				pilih=1;
			}
		}else if(a==13){
			break;
		}
	}
	if(pilih==1){
		query_tm();
	}
	else if(pilih==2){
		query_m();
	}
	else if(pilih==3){
		query_p();
	}
	else {
		query_bph();
	}
		
}

void query_tm(){
	int pilih=1;
	while(1){
		char a;
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("       ===>>[          QUERY          ]<<===      \n\n");
		printf("       ===>>[     TRANSAKSI MASUK     ]<<===      \n\n");
		if(pilih==1){
			printf("Berdasarkan : => Id\n");
			printf("                 Tanggal\n");
			printf("                 Metode Pembayaran\n");
		}
		else if(pilih==2){
			printf("Berdasarkan :    Id\n");
			printf("              => Tanggal\n");
			printf("                 Metode Pembayaran\n");
		}
		else {
			printf("Berdasarkan :    Id\n");
			printf("                 Tanggal\n");
			printf("              => Metode Pembayaran\n");
		}
		a=getch();
		if(a==72){
			pilih--;
			if(pilih<1){
				pilih=3;
			}
		}else if(a==80){
			pilih++;
			if(pilih>3){
				pilih=1;
			}
		}else if(a==13){
			break;
		}
	}
	if(pilih==1){
		query_tm_id();
	}
	else if(pilih==2){
		query_tm_tgl();
	}
	else{
		query_tm_mp();
	}
}

void query_m(){
	int pilih=1;
	while(1){
		char a;
		/*struct mahasiswa{
		ll nrp;
		char nama[50];
		ll notelp;
		struct mahasiswa *next;
		struct mahasiswa *prev;
		};*/
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("       ===>>[          QUERY          ]<<===      \n\n");
		printf("       ===>>[        MAHASISWA        ]<<===      \n\n");
		if(pilih==1){
			printf("Berdasarkan : => NRP\n");
			printf("                 Nama\n");
			printf("                 Nomor Telepon\n");
		}
		else if(pilih==2){
			printf("Berdasarkan :    NRP\n");
			printf("              => Nama\n");
			printf("                 Nomor Telepon\n");
		}
		else {
			printf("Berdasarkan :    NRP\n");
			printf("                 Nama\n");
			printf("              => Nomor Telepon\n");
		}
		a=getch();
		if(a==72){
			pilih--;
			if(pilih<1){
				pilih=3;
			}
		}else if(a==80){
			pilih++;
			if(pilih>3){
				pilih=1;
			}
		}else if(a==13){
			break;
		}
	}
	if(pilih==1){
		query_m_nrp();
	}
	else if(pilih==2){
		query_m_nama();
	}
	else{
		query_m_notelp();
	}
}

void query_p(){
	/*struct produk{
			int id;
			char nama[50];
			int harga;
			struct tanggal tgl;
			int id_tm;
			struct produk *next;
			struct produk *prev;
			};*/
	int pilih=1;
	while(1){
		char a;
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("       ===>>[          QUERY          ]<<===      \n\n");
		printf("       ===>>[          PRODUK         ]<<===      \n\n");
		if(pilih==1){
			printf("Berdasarkan : => Id\n");
			printf("                 Nama\n");
			printf("                 Tanggal Diterima\n");
		}
		else if(pilih==2){
			printf("Berdasarkan :    Id\n");
			printf("              => Nama\n");
			printf("                 Tanggal Diterima\n");
		}
		else {
			printf("Berdasarkan :    Id\n");
			printf("                 Nama\n");
			printf("              => Tanggal Diterima\n");
		}
		a=getch();
		if(a==72){
			pilih--;
			if(pilih<1){
				pilih=3;
			}
		}else if(a==80){
			pilih++;
			if(pilih>3){
				pilih=1;
			}
		}else if(a==13){
			break;
		}
	}
	if(pilih==1){
		query_p_id();
	}
	else if(pilih==2){
		query_p_nama();
	}
	else{
		query_p_tgl();
	}
}
void query_bph(){

	int pilih=1;
	while(1){
		char a;
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("       ===>>[          QUERY          ]<<===      \n\n");
		printf("       ===>>[           BPH           ]<<===      \n\n");
		/*struct Bph{
		ll nrp;
		char nama[50];
		ll notelp;
		char jabatan[50];
		char pw[50];
		struct Bph *next;
		struct Bph *prev;
		};*/
		if(pilih==1){
			printf("Berdasarkan : => NRP\n");
			printf("                 Nama\n");
			printf("                 Nomor Telepon\n");
			printf("                 Jabatan\n");
		}
		else if(pilih==2){
			printf("Berdasarkan :    NRP\n");
			printf("              => Nama\n");
			printf("                 Nomor Telepon\n");
			printf("                 Jabatan\n");
		}
		else if(pilih==3) {
			printf("Berdasarkan :    NRP\n");
			printf("                 Nama\n");
			printf("              => Nomor Telepon\n");
			printf("                 Jabatan\n");
		}
		else {
			printf("Berdasarkan :    NRP\n");
			printf("                 Nama\n");
			printf("                 Nomor Telepon\n");
			printf("              => Jabatan\n");
		}
		a=getch();
		if(a==72){
			pilih--;
			if(pilih<1){
				pilih=4;
			}
		}else if(a==80){
			pilih++;
			if(pilih>4){
				pilih=1;
			}
		}else if(a==13){
			break;
		}
	}
	if(pilih==1){
		query_bph_nrp();
	}
	else if(pilih==2){
		query_bph_nama();
	}
	else if(pilih==3){
		query_bph_notelp();
	}
	else {
		query_bph_jabatan();
	}

}

void query_tm_id(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[     TRANSAKSI MASUK     ]<<===      \n\n");
	printf("Berdasarkan : => Id\n");
	int temp;
	struct transaksi_masuk *cur=tmhead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Id : ");scanf("%d",&temp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(cur->id==temp){
			printf("Id       : %d\nTanggal  : %d %d %d\nMetode   : %s\nJumlah   : %d\nNRP_Mhs  : %lld\nNRP_BPH  : %lld\n",cur->id,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->metode_pembayaran,cur->jumlah,cur->nrp_mhs,cur->nrp_bph);
		}
		cur=cur->next;
	}
	system("pause");
	home();
	
}
void query_tm_tgl(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[     TRANSAKSI MASUK     ]<<===      \n\n");
	printf("Berdasarkan : => Tanggal\n");
	int hari,bulan,tahun;
	struct transaksi_masuk *cur=tmhead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Hari : ");scanf("%d",&hari);
	printf("Masukkan Bulan : ");scanf("%d",&bulan);
	printf("Masukkan Tahun : ");scanf("%d",&tahun);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(((cur->tgl).hari==hari)&&((cur->tgl).bulan==bulan)&&((cur->tgl).tahun==tahun)){
			printf("Id       : %d\nTanggal  : %d %d %d\nMetode   : %s\nJumlah   : %d\nNRP_Mhs  : %lld\nNRP_BPH  : %lld\n",cur->id,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->metode_pembayaran,cur->jumlah,cur->nrp_mhs,cur->nrp_bph);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_tm_mp(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[     TRANSAKSI MASUK     ]<<===      \n\n");
	printf("Berdasarkan : => Metode Pembayaran\n");
	char mp[15];
	struct transaksi_masuk *cur=tmhead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Metode Pembayaran : ");scanf("%s",mp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(strcmp(mp,cur->metode_pembayaran)==0){
			printf("Id       : %d\nTanggal  : %d %d %d\nMetode   : %s\nJumlah   : %d\nNRP_Mhs  : %lld\nNRP_BPH  : %lld\n",cur->id,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->metode_pembayaran,cur->jumlah,cur->nrp_mhs,cur->nrp_bph);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_m_nrp(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[        MAHASISWA        ]<<===      \n\n");
	printf("Berdasarkan : => NRP\n");
	ll nrp;
	struct mahasiswa *cur=mhead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan NRP : ");scanf("%lld",&nrp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(nrp==cur->nrp){
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\n",cur->nrp,cur->nama,cur->notelp);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_m_nama(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[        MAHASISWA        ]<<===      \n\n");
	printf("Berdasarkan : => Nama\n");
	char nama[50];
	struct mahasiswa *cur=mhead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Nama : ");scanf("%s",nama);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(strcmp(nama,cur->nama)==0){
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\n",cur->nrp,cur->nama,cur->notelp);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_m_notelp(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[        MAHASISWA        ]<<===      \n\n");
	printf("Berdasarkan : => Nomor Telepon\n");
	ll notelp;
	struct mahasiswa *cur=mhead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Nomor Telepon : ");scanf("%lld",&notelp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(notelp==cur->notelp){
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\n",cur->nrp,cur->nama,cur->notelp);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_p_id(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[          PRODUK         ]<<===      \n\n");
	printf("Berdasarkan : => Id\n");
	int temp;
	struct produk *cur=phead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Id : ");scanf("%d",&temp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(cur->id==temp){
			printf("Id       : %d\nNama     : %s\nHarga    : %d\nTanggal  : %d %d %d\nId_TM    : %d\n",cur->id,cur->nama,cur->harga,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->id_tm);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_p_nama(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[          PRODUK         ]<<===      \n\n");
	printf("Berdasarkan : => Nama\n");
	char nama[50];
	struct produk *cur=phead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Id : ");scanf("%s",nama);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(strcmp(cur->nama,nama)==0){
			printf("Id       : %d\nNama     : %s\nHarga    : %d\nTanggal  : %d %d %d\nId_TM    : %d\n",cur->id,cur->nama,cur->harga,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->id_tm);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_p_tgl(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[          PRODUK         ]<<===      \n\n");
	printf("Berdasarkan : => Tanggal Diterima\n");
	int hari,bulan,tahun;
	struct produk *cur=phead;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Hari : ");scanf("%d",&hari);
	printf("Masukkan Bulan : ");scanf("%d",&bulan);
	printf("Masukkan Tahun : ");scanf("%d",&tahun);
	printf("Hasil : \n");
	while(cur!=NULL){
		if(((cur->tgl).hari==hari)&&((cur->tgl).bulan==bulan)&&((cur->tgl).tahun==tahun)){
			printf("Id       : %d\nNama     : %s\nHarga    : %d\nTanggal  : %d %d %d\nId_TM    : %d\n",cur->id,cur->nama,cur->harga,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->id_tm);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_bph_nrp(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[           BPH           ]<<===      \n\n");
	printf("Berdasarkan : => NRP\n");
	ll nrp;
	struct Bph *cur=head;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan NRP : ");scanf("%lld",&nrp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(nrp==cur->nrp){
			/*NRP      : 5025231182
			  Nama     : Udin
			  No. Telp : 85322900129
			  Jabatan  : Bendahara
			  Password : Udin.99*/
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\nJabatan  : %s\n\n",cur->nrp,cur->nama,cur->notelp,cur->jabatan);
		}
		cur=cur->next;
	}
	system("pause");
	home();
	
}
void query_bph_nama(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[           BPH           ]<<===      \n\n");
	printf("Berdasarkan : => Nama\n");
	char nama[50];
	struct Bph *cur=head;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);;
	printf("Masukkan Nama : ");scanf("%s",nama);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(strcmp(cur->nama,nama)==0){
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\nJabatan  : %s\n\n",cur->nrp,cur->nama,cur->notelp,cur->jabatan);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}
void query_bph_notelp(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[           BPH           ]<<===      \n\n");
	printf("Berdasarkan : => Nomor Telepon\n");
	ll notelp;
	struct Bph *cur=head;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan NRP : ");scanf("%lld",&notelp);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(notelp==cur->notelp){
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\nJabatan  : %s\n\n",cur->nrp,cur->nama,cur->notelp,cur->jabatan);
		}
		cur=cur->next;
	}
	system("pause");
	home();

}
void query_bph_jabatan(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("       ===>>[          QUERY          ]<<===      \n\n");
	printf("       ===>>[           BPH           ]<<===      \n\n");
	printf("Berdasarkan : => Jabatan\n");
	char jabatan[50];
	struct Bph *cur=head;
	int c;
    while ((c = getchar()) != '\n' && c != EOF);
	printf("Masukkan Nama : ");scanf("%s",jabatan);
	printf("     Hasil : \n");
	while(cur!=NULL){
		if(strcmp(cur->jabatan,jabatan)==0){
			printf("NRP      : %lld\nNama     : %s\nNo. Telp : %lld\nJabatan  : %s\n\n",cur->nrp,cur->nama,cur->notelp,cur->jabatan);
		}
		cur=cur->next;
	}
	system("pause");
	home();
}

void update(){
    
    int pilih=1;
    char a;
    while(1){
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("|      ===>>[         UPDATE          ]<<===      |\n\n");

        if(pilih==1){
            printf("|=================================================|\n");
            printf("|                                                 |\n");
            printf("|      ===>>[     TRANSAKSI MASUK     ]<<===      |\n");
            printf("|           [        MAHASISWA        ]           |\n");
            printf("|           [         PRODUK          ]           |\n");
            printf("|                                                 |\n");
            printf("|=================================================|\n");
        }else if(pilih==2){
            printf("|=================================================|\n");
            printf("|                                                 |\n");
            printf("|           [     TRANSAKSI MASUK     ]           |\n");
            printf("|      ===>>[        MAHASISWA        ]<<===      |\n");
            printf("|           [         PRODUK          ]           |\n");
            printf("|                                                 |\n");
            printf("|=================================================|\n");
        }else{
            printf("|=================================================|\n");
            printf("|                                                 |\n");
            printf("|           [     TRANSAKSI MASUK     ]           |\n");
            printf("|           [        MAHASISWA        ]           |\n");
            printf("|      ===>>[         PRODUK          ]<<===      |\n");
            printf("|                                                 |\n");
            printf("|=================================================|\n");
        }
        
        a=getch();
        if(a==72){
            pilih--;
            if(pilih<1){
                pilih=3;
            }
        }else if(a==80){
            pilih++;
            if(pilih>3){
                pilih=1;
            }
        }else if(a==13){
            break;
        }
    }
    if(pilih==3){
		update_p();
	}
	else if(pilih==1){
        update_tm();
	}
	else if(pilih==2){
		update_m();
	}

}
void update_tm(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("|      ===>>[         UPDATE          ]<<===      |\n\n");
	printf("|      ===>>[     TRANSAKSI MASUK     ]<<===      |\n\n");
	int id;
	printf("Masukkan Id Transaksi Masuk : ");scanf("%d",&id);
	int hari,bulan,tahun,jumlah;
	char mp[15];
	printf("Masukkan tanggal transaksi baru : ");scanf("%d %d %d",&hari,&bulan,&tahun);
	printf("Masukkan jumlah transaksi  baru : ");scanf("%d",&jumlah);
	printf("Masukkan metode pembayaran baru : ");scanf("%s",mp);
	struct transaksi_masuk *cur=tmhead;
	while(cur!=NULL){
		if(cur->id==id){
			strcpy(cur->metode_pembayaran,mp);
			(cur->tgl).hari=hari;
			(cur->tgl).bulan=bulan;
			(cur->tgl).tahun=tahun;
			cur->jumlah=jumlah;
			break;
		}
		else cur=cur->next;
	}
	printf("Data transaksi masuk berhasil di-update!\n");
	system("pause");
	home();
}
void update_m(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("|      ===>>[         UPDATE          ]<<===      |\n\n");
	printf("|      ===>>[        MAHASISWA        ]<<===      |\n\n");
	ll nrp;
	printf("Masukkan NRP Mahasiswa : ");scanf("%lld",&nrp);
	ll notelp;
	char nama[50];
	printf("Masukkan nama baru              : ");scanf("%s",nama);
	printf("Masukkan nomor telepon baru     : ");scanf("%lld",&notelp);

	struct mahasiswa *cur=mhead;
	while(cur!=NULL){
		if(cur->nrp==nrp){
			strcpy(cur->nama,nama);
			cur->notelp=notelp;
			break;
		}
		else cur=cur->next;
	}
	printf("Data mahasiswa berhasil di-update!\n");
	system("pause");
	home();
}
void update_p(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("|      ===>>[         UPDATE          ]<<===      |\n\n");
	printf("|      ===>>[         PRODUK          ]<<===      |\n\n");
	int id;
	printf("Masukkan Id Produk : ");scanf("%d",&id);
	int hari,bulan,tahun,harga;
	char nama[50];
	printf("Masukkan nama produk yang baru  : ");scanf("%s",nama);
	printf("Masukkan harga baru dari produk : ");scanf("%d",&harga);
	printf("Masukkan tanggal diterima baru  : ");scanf("%d %d %d",&hari,&bulan,&tahun);
	
	struct produk *cur=phead;
	while(cur!=NULL){
		if(cur->id==id){
			strcpy(cur->nama,nama);
			cur->harga=harga;
			(cur->tgl).hari=hari;
			(cur->tgl).bulan=bulan;
			(cur->tgl).tahun=tahun;
			break;
		}
		else cur=cur->next;
	}
	printf("Data produk berhasil di-update!\n");
	system("pause");
	home();
}

void hapus(){
	int pilih=1;
    char a;
    while(1){
		system("cls");
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
		printf("*                     TC'23                      *\n");
		printf("*                                                *\n");
		printf("**************************************************\n\n");
		printf("|      ===>>[         DELETE          ]<<===      |\n\n");

        if(pilih==1){
            printf("|=================================================|\n");
            printf("|                                                 |\n");
            printf("|      ===>>[     TRANSAKSI MASUK     ]<<===      |\n");
            printf("|           [        MAHASISWA        ]           |\n");
            printf("|           [         PRODUK          ]           |\n");
            printf("|                                                 |\n");
            printf("|=================================================|\n");
        }else if(pilih==2){
            printf("|=================================================|\n");
            printf("|                                                 |\n");
            printf("|           [     TRANSAKSI MASUK     ]           |\n");
            printf("|      ===>>[        MAHASISWA        ]<<===      |\n");
            printf("|           [         PRODUK          ]           |\n");
            printf("|                                                 |\n");
            printf("|=================================================|\n");
        }else{
            printf("|=================================================|\n");
            printf("|                                                 |\n");
            printf("|           [     TRANSAKSI MASUK     ]           |\n");
            printf("|           [        MAHASISWA        ]           |\n");
            printf("|      ===>>[         PRODUK          ]<<===      |\n");
            printf("|                                                 |\n");
            printf("|=================================================|\n");
        }
        a=getch();
        if(a==72){
            pilih--;
            if(pilih<1){
                pilih=3;
            }
        }else if(a==80){
            pilih++;
            if(pilih>3){
                pilih=1;
            }
        }else if(a==13){
            break;
        }
    }
    if(pilih==3){
		hapus_p();
	}
	else if(pilih==1){
        hapus_tm();
	}
	else if(pilih==2){
		hapus_m();
	}

}
void hapus_tm(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("|      ===>>[         DELETE          ]<<===      |\n\n");
	printf("|      ===>>[     TRANSAKSI MASUK     ]<<===      |\n");
	int id;
	printf("Masukkan id dari transaksi masuk yang ingin dihapus : ");scanf("%d",&id);
	struct transaksi_masuk *cur=tmhead;
	while(cur!=NULL){
		if(cur->id==id){
			if(cur->prev==NULL){
				if(cur->next==NULL){
					tmhead=NULL;
					tmtail=NULL;
					
				}
				else {
					tmhead=cur->next;
					tmhead->prev=NULL;
				}
				
			}
			else if(cur->next==NULL){
				tmtail=cur->prev;
				tmtail->next=NULL;
			}
			else {
				(cur->prev)->next=cur->next;
				(cur->next)->prev=cur->prev;
			}
			free(cur);
			break;

		}
		else cur=cur->next;
	}
	printf("Data transaksi masuk berhasil dihapus !\n");
	system("pause");
	home();

}
void hapus_m(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("|      ===>>[         DELETE          ]<<===      |\n\n");
	printf("|      ===>>[        MAHASISWA        ]<<===      |\n");
	ll nrp;
	printf("Masukkan nrp dari mahasiswa yang ingin dihapus : ");scanf("%lld",&nrp);
	struct mahasiswa *cur=mhead;
	while(cur!=NULL){
		if(cur->nrp==nrp){
			if(cur->prev==NULL){
				if(cur->next!=NULL){
					mhead=cur->next;
					mhead->prev=NULL;
				}
				else{
					mhead=NULL;
					mtail=NULL;
				}
				
			}
			else if(cur->next==NULL){
				mtail=cur->prev;
				mtail->next=NULL;
			}
			else {
				(cur->prev)->next=cur->next;
				(cur->next)->prev=cur->prev;
			}
			free(cur);
			break;
		}
		else cur=cur->next;
	}
	printf("Data mahasiswa berhasil dihapus !\n");
	system("pause");
	home();
}
void hapus_p(){
	system("cls");
	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("*        BASIS DATA PENJUALAN MERCHANDISE        *\n");
	printf("*                     TC'23                      *\n");
	printf("*                                                *\n");
	printf("**************************************************\n\n");
	printf("|      ===>>[         DELETE          ]<<===      |\n\n");
	printf("|      ===>>[         PRODUK          ]<<===      |\n");
	int id;
	printf("Masukkan id dari produk yang ingin dihapus : ");scanf("%d",&id);
	struct produk *cur=phead;
	while(cur!=NULL){
		if(cur->id==id){
			if(cur->prev==NULL){
				if(cur->next!=NULL){
					phead=cur->next;
					phead->prev=NULL;
				}
				else {
					phead=NULL;
					ptail=NULL;
				}
				
			}
			else if(cur->next==NULL){
				ptail=cur->prev;
				ptail->next=NULL;
			}
			else {
				(cur->prev)->next=cur->next;
				(cur->next)->prev=cur->prev;
			}
			free(cur);
			break;

		}
		else cur=cur->next;
	}
	printf("Data produk berhasil dihapus !\n");
	system("pause");
	home();
}
void keluar(){
	FILE *mfile=fopen("mhs.txt","w");
	FILE *tmfile=fopen("tm.txt","w");
	FILE *pfile=fopen("p.txt","w");
	
	struct transaksi_masuk *cur=tmhead;
	while(cur!=NULL){
		fprintf(tmfile,"Id       : %d\nTanggal  : %d %d %d\nMetode   : %s\nJumlah   : %d\nNRP_Mhs  : %lld\nNRP_BPH  : %lld\n",cur->id,(cur->tgl).hari,(cur->tgl).bulan,(cur->tgl).tahun,cur->metode_pembayaran,cur->jumlah,cur->nrp_mhs,cur->nrp_bph);
		cur=cur->next;
	}
	struct mahasiswa *curm=mhead;
	while(curm!=NULL){
		fprintf(mfile,"NRP      : %lld\nNama     : %s\nNo. Telp : %lld\n",curm->nrp,curm->nama,curm->notelp);
		curm=curm->next;
	}
	struct produk *curp=phead;
	while(curp!=NULL){
		fprintf(pfile,"Id       : %d\nNama     : %s\nHarga    : %d\nTanggal  : %d %d %d\nId_TM    : %d\n",curp->id,curp->nama,curp->harga,(curp->tgl).hari,(curp->tgl).bulan,(curp->tgl).tahun,curp->id_tm);
		curp=curp->next;
	}
	fclose(tmfile);
	fclose(mfile);
	fclose(pfile);
	return ;

}