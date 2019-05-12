#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

struct Mahasiswa{
	string nama;
	string jurusan;
	string nim;
};

struct buku{
	string judul;
	string kode;
	string pinjam, pengembalian;
	Mahasiswa mahasiswa;
}perpus[100], temp;

int getOption(int &pilih);
int getOptionSearch(int &pilih);
int getOptionSort(int &pilih);
int getOptionTransaksi(int &pilih);
void writeData(fstream &data, int &jmlData, buku perpus[], string &myFile);
void input(fstream &data, int &jmlData, string &myFile);
void output(int &jmlData);
void readData(ifstream &dataIn, int &jmlData, buku perpus[], string &myFile);
void sequential(int &jmlData, buku perpus[]);
void bubble(buku perpus[], int &jmlData);
void selection(buku perpus[], int &jmlData);
void insertion(buku perpus[], int &jmlData);
void shell(buku perpus[], int &jmlData);
void merge(buku perpus[], int l, int m, int r);
void mergeSort(buku perpus[], int l, int r);
void quick(buku perpus[], int first, int last);
void writeDataSort(fstream &data, int &jmlData, buku perpus[], string &myFile);
void binary(int &jmlData, buku perpus[]);
void readDataMerging(ifstream &dataIn, int &jmlData, buku perpus[], string &myFile);
void writeDataMerging(fstream &data, int &jmlData, buku perpus[], string &myFileTransaksi);
void readDataMergingSambung(ifstream &dataIn, int &jmlData, buku perpus[], string &myFileTransaksi);
void readDataMergingUrut(fstream &data, ifstream &dataIn, int &jmlData, buku perpus[], string &myFileTransaksi);
void splitting(ifstream &dataIn, fstream &data, int &jmlData, buku perpus[]);

int main(){
	fstream data;
	ifstream dataIn;
	string myFile, myFileTransaksi;
	char is_continue;
	int pilih, jmlData;
	
	enum option{INPUT = 1, SEARCHING, TRANSAKSI, EXIT};
	enum optionSearch{SEQUENTIAL = 1, BINARY, BACK};
	enum optionSort{BUBBLE = 1, SELECTION, INSERTION, SHELL, MERGE, QUICK};
	enum optionTransaksi{MERGING_SAMBUNG = 1, MERGING_URUT, SPLITTING};
	
	int pilihan = getOption(pilih);
	while(pilihan != EXIT){
		switch(pilihan){
			case INPUT :
				input(data, jmlData, myFile);
				break;
			case SEARCHING :
				pilihan = getOptionSearch(pilih);
				switch(pilihan){
					case SEQUENTIAL :
						cout << "\nSequential Search" << endl;
						readData(dataIn, jmlData, perpus, myFile);
						sequential(jmlData, perpus);
						break;
					case BINARY :
						pilihan = getOptionSort(pilih);
						switch(pilihan){
							case BUBBLE :
								cout << "\nBubble Sort" << endl;
								readData(dataIn, jmlData, perpus, myFile);
								bubble(perpus, jmlData);
								writeDataSort(data, jmlData, perpus, myFile);
								binary(jmlData, perpus);
								break;
							case SELECTION :
								cout << "\nSelection Sort" << endl;
								readData(dataIn, jmlData, perpus, myFile);
								selection(perpus, jmlData);
								writeDataSort(data, jmlData, perpus, myFile);
								binary(jmlData, perpus);
								break;
							case INSERTION :
								cout << "\nInsertion Sort" << endl;
								readData(dataIn, jmlData, perpus, myFile);
								insertion(perpus, jmlData);
								writeDataSort(data, jmlData, perpus, myFile);
								binary(jmlData, perpus);
								break;
							case SHELL :
								cout << "\nShell Sort" << endl;
								readData(dataIn, jmlData, perpus, myFile);
								shell(perpus, jmlData);
								writeDataSort(data, jmlData, perpus, myFile);
								binary(jmlData, perpus);
								break;
							case MERGE :
								cout << "\nMerge Sort" << endl;
								readData(dataIn, jmlData, perpus, myFile);
								mergeSort(perpus, 0, jmlData-1);
								output(jmlData);
								writeDataSort(data, jmlData, perpus, myFile);
								binary(jmlData, perpus);
								break;
							case QUICK :
								cout << "\nQuick Sort" << endl;
								readData(dataIn, jmlData, perpus, myFile);
								quick(perpus, 0, jmlData-1);
								output(jmlData);
								writeDataSort(data, jmlData, perpus, myFile);
								binary(jmlData, perpus);
								break;
							default :
								cout << "Pilihan tidak ditemukan" << endl;
								break;
						}
						break;
					case BACK :
						pilihan = getOption(pilih);
						break;
					default :
						cout << "Pilihan tidak ditemukan" << endl;
						break;
				}
				break;
			case TRANSAKSI:
				pilihan = getOptionTransaksi(pilih);
				switch(pilihan){
					case MERGING_SAMBUNG :
						cout << "\nMerging Sambung" << endl;
						cout << "\n-----------------------------------\n";
						cout << "\nMasukkan nama file hasil transaksi : "; cin >> myFileTransaksi;
						cout << "\n-----------------------------------\n";
						cout << "Masukan nama file pertama : "; 
						readDataMerging(dataIn, jmlData, perpus, myFile);
						writeDataMerging(data, jmlData, perpus, myFileTransaksi);
						cout << "\n-----------------------------------\n";
						cout << "Masukan nama file kedua : "; 
						readDataMerging(dataIn, jmlData, perpus, myFile);
						writeDataMerging(data, jmlData, perpus, myFileTransaksi);
						cout << "\n===================================\n";
						cout << "Hasil merging sambung" << endl;
						readDataMergingSambung(dataIn, jmlData, perpus, myFileTransaksi);
						break;
					case MERGING_URUT :
						cout << "\nMerging Urut" << endl;
						cout << "\n-----------------------------------\n";
						cout << "\nMasukkan nama file hasil transaksi : "; cin >> myFileTransaksi;
						cout << "\n-----------------------------------\n";
						cout << "Masukan nama file pertama : "; 
						readDataMerging(dataIn, jmlData, perpus, myFile);
						writeDataMerging(data, jmlData, perpus, myFileTransaksi);
						cout << "\n-----------------------------------\n";
						cout << "Masukan nama file kedua : "; 
						readDataMerging(dataIn, jmlData, perpus, myFile);
						writeDataMerging(data, jmlData, perpus, myFileTransaksi);
						cout << "\n===================================\n";
						cout << "Hasil merging Urut" << endl;
						readDataMergingUrut(data, dataIn, jmlData, perpus, myFileTransaksi);
						break;
					case SPLITTING :
						cout << "\nSplitting" << endl;
						cout << "\n-----------------------------------\n";
						readData(dataIn, jmlData, perpus, myFile);
						splitting(dataIn, data, jmlData, perpus);
						break;
					default :
						cout << "Pilihan tidak ditemukan" << endl;
						break;
				}
				break;
			default:
				cout << "Pilihan tidak ditemukan" << endl;
				break;
		}
		
		label_continue:
		
		cout << "\n\nLanjutkan?(y/n) : ";
		cin >> is_continue;
		if ( (is_continue == 'y') | (is_continue == 'Y')){
			pilihan = getOption(pilih);
		} else if ((is_continue == 'n') | (is_continue == 'N')){
			break;
		} else {
			goto label_continue;
		}
	}
	
	cout << "\n\nAkhir dari program" << endl;
	
	return 0;
}

int getOption(int &pilih){
	system("cls");
	cout << "Menu" << endl;
	cout << "==================" << endl;
	cout << "1. Input Data" << endl;
	cout << "2. Searching" << endl;
	cout << "3. Transaksi" << endl;
	cout << "4. Exit" << endl;
	cout << "==================" << endl;
	cout << "Pilih [1-4]? : "; cin >> pilih;
	
	return pilih;
}

int getOptionSearch(int &pilih){
	system("cls");
	cout << "Menu Searching" << endl;
	cout << "========================" << endl;
	cout << "1. Sequential" << endl;
	cout << "2. Binary Search" << endl;
	cout << "3. Kembali ke Menu Utama" << endl;
	cout << "========================" << endl;
	cout << "Pilih Searching [1-3] : "; cin >> pilih;
	
	return pilih;
}

int getOptionSort(int &pilih){
	system("cls");
	cout << "Menu Sorting" << endl;
	cout << "========================" << endl;
	cout << "1. Bubble Sort" << endl;
	cout << "2. Selection Sort" << endl;
	cout << "3. Insertion Sort" << endl;
	cout << "4. Shell Sort" << endl;
	cout << "5. Merge Sort" << endl;
	cout << "6. Quick Sort" << endl;
	cout << "========================" << endl;
	cout << "Pilih Sorting [1-6] : "; cin >> pilih;
	
	return pilih;
}

int getOptionTransaksi(int &pilih){
	system("cls");
	cout << "Menu Transaksi" << endl;
	cout << "========================" << endl;
	cout << "1. Merging Sambung" << endl;
	cout << "2. Merging Urut" << endl;
	cout << "3. Splitting" << endl;
	cout << "========================" << endl;
	cout << "Pilih Sorting [1-3] : "; cin >> pilih;
	
	return pilih;
}

void writeData(fstream &data, int &jmlData, buku perpus[], string &myFile){
	data.open(myFile, ios::trunc | ios::out);
	
	for(int i = 0; i < jmlData; i++){
		data << perpus[i].mahasiswa.nama << endl;
		data << perpus[i].mahasiswa.nim << endl;
		data << perpus[i].mahasiswa.jurusan << endl;
		data << perpus[i].judul << endl;
		data << perpus[i].kode << endl;
		data << perpus[i].pinjam << endl;
		data << perpus[i].pengembalian << endl;
	}
	data.close();
}

void input(fstream &data, int &jmlData, string &myFile){
	cout << "Masukkan nama file : "; cin >> myFile;
	cout << "Masukkan jumlah data peminjam : "; cin >> jmlData;
	cin.ignore();
	for(int i = 0; i < jmlData; i++){
		cout << "\nData peminjam buku ke-" << i+1 << endl;
		cout << "Nama : ";
		getline(cin, perpus[i].mahasiswa.nama);
		cout << "NIM : "; cin >> perpus[i].mahasiswa.nim;
		cout << "Jurusan : ";
		cin.ignore(); getline(cin, perpus[i].mahasiswa.jurusan);
		cout << "Judul Buku : ";
		getline(cin, perpus[i].judul);
		cout << "Kode Buku : "; cin >> perpus[i].kode;
		cout << "Tanggal/Bulan/Tahun Pinjam : ";
		cin.ignore(); getline(cin, perpus[i].pinjam);
		cout << "Tanggal/Bulan/Tahun Pengembalian : ";
		getline(cin, perpus[i].pengembalian);
	}
	writeData(data, jmlData, perpus, myFile);
}

void output(int &jmlData){
	cout << "\n-----------------------------------\n";
	cout << "\nData yang sudah di urutkan\n";
	for(int i = 0; i < jmlData; i++){
		cout << "\nData peminjam buku ke-" << i+1 << endl;
		cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
		cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
		cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
		cout << "Judul Buku : " << perpus[i].judul << endl;
		cout << "Kode Buku : " << perpus[i].kode << endl;
		cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
		cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
	}
}

void readData(ifstream &dataIn, int &jmlData, buku perpus[], string &myFile){
	label_continue :
	int i = 0;
	cout << "Masukan nama file : "; cin >> myFile;
	dataIn.open(myFile, ios::in);
	if(dataIn.is_open()){
		while(!dataIn.eof()){
			getline(dataIn, perpus[i].mahasiswa.nama);
			getline(dataIn, perpus[i].mahasiswa.nim);
			getline(dataIn, perpus[i].mahasiswa.jurusan);
			getline(dataIn, perpus[i].judul);
			getline(dataIn, perpus[i].kode);
			getline(dataIn, perpus[i].pinjam);
			getline(dataIn, perpus[i].pengembalian);
			
			i++;
		}
		jmlData = i-1;
		dataIn.close();
		for(int i = 0; i < jmlData ; i++){
			cout << "\nData peminjam buku ke-" << i+1 << endl;
			cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
			cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
			cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
			cout << "Judul Buku : " << perpus[i].judul << endl;
			cout << "Kode Buku : " << perpus[i].kode << endl;
			cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
			cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
		}
	}else{
		cout << "File " << myFile << " tidak ditemukan" << endl;
		dataIn.close();
		goto label_continue;
	}
}

void sequential(int &jmlData, buku perpus[]){
	bool found = false;
	string cariNama;
	int i = 0;
	cout << "\n-----------------------------------\n";
	cout << "\nMasukkan nama yang dicari : "; cin.ignore(); getline(cin, cariNama);
	while((i < jmlData) & (!found)){
		if(perpus[i].mahasiswa.nama == cariNama){
			found = true;
		}else{
			i += 1;
		}
	}
	if(found){
		cout << "\nDitemukan pada data peminjam buku ke-" << i+1 << endl;
		cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
		cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
		cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
		cout << "Judul Buku : " << perpus[i].judul << endl;
		cout << "Kode Buku : " << perpus[i].kode << endl;
		cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
		cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
	}else{
		cout << cariNama << " tidak ditemukan" << endl;
	}
}

void bubble(buku perpus[], int &jmlData){
	int i, j;
	for(i=0; i < jmlData-1; i++){
		for(j=0; j < jmlData-1-i; j++){
			if(perpus[j].mahasiswa.nama > perpus[j+1].mahasiswa.nama){
				temp = perpus[j];
				perpus[j] = perpus[j+1];
				perpus[j+1] = temp;
			}
		}
	}
	output(jmlData);
}

void selection(buku perpus[], int &jmlData){
	int i, j;
	for(i = 0; i < jmlData; i++){
		for(j = i+1; j < jmlData; j++){
			if(perpus[i].mahasiswa.nama > perpus[j].mahasiswa.nama){
				temp = perpus[i];
				perpus[i] = perpus[j];
				perpus[j] = temp;
			}
		}
	}
	output(jmlData);
}

void insertion(buku perpus[], int &jmlData){
	int i, j;
	for(i=1; i < jmlData; i++){
		temp = perpus[i];
		j = i - 1;
		while((temp.mahasiswa.nama < perpus[j].mahasiswa.nama) & (j >= 0)){
			perpus[j+1] = perpus[j];
			j = j - 1;
			perpus[j+1] = temp;
		}
	}
	output(jmlData);
}

void shell(buku perpus[], int &jmlData){
	int i = 0, j = 0, k = 0;
	for(k = jmlData/2; k > 0; k /= 2){
		for(j = k; j < jmlData; j++){
			for(i = j-k; i >= 0; i -= k){
				if(perpus[i + k].mahasiswa.nama >= perpus[i].mahasiswa.nama){
					break;
				}else{
					temp = perpus[i];
					perpus[i] = perpus[i + k];
					perpus[i + k] = temp;
				}
			}
		}
	}
	output(jmlData);
}

void merge(buku perpus[], int l, int m, int r){ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 =  r - m; 
	buku L[n1], R[n2]; 

	for (i = 0; i < n1; i++){
		L[i] = perpus[l + i];
	}
	for (j = 0; j < n2; j++){
		R[j] = perpus[m + 1+ j]; 
	}

	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2){ 
		if(L[i].mahasiswa.nama <= R[j].mahasiswa.nama){ 
			perpus[k] = L[i]; 
			i++; 
		}else{ 
			perpus[k] = R[j]; 
			j++; 
		}
		k++; 
	}
	while (i < n1){ 
		perpus[k] = L[i]; 
		i++; 
		k++; 
	}
	while (j < n2){
		perpus[k] = R[j]; 
		j++; 
		k++; 
	}
}
  
void mergeSort(buku perpus[], int l, int r){
	if (l < r){ 
		int m = l+(r-l)/2; 
		
		mergeSort(perpus, l, m); 
		mergeSort(perpus, m+1, r);
		
		merge(perpus, l, m, r); 
	}
}

void quick(buku perpus[], int first, int last){
	int low, high;
	buku list_separator;
	low = first;
	high = last;
	list_separator = perpus[(first + last) / 2];
	do{
		while(perpus[low].mahasiswa.nama < list_separator.mahasiswa.nama){
		low++;
		}
		while(perpus[high].mahasiswa.nama > list_separator.mahasiswa.nama){
		high--;
		}
		if(low <= high){
			temp = perpus[low];
			perpus[low++] = perpus[high];
			perpus[high--] = temp;
		}
	}while(low <= high);
	if(first < high){
		quick(perpus, first, high);
	}
	if(low < last){ 
		quick(perpus, low, last);
	}
}

void writeDataSort(fstream &data, int &jmlData, buku perpus[], string &myFile){
	cout << "\n-----------------------------------\n";
	cout << "\nMasukkan nama file hasil sorting : "; cin >> myFile;
	data.open(myFile, ios::trunc | ios::out);
	
	for(int i = 0; i < jmlData; i++){
		data << perpus[i].mahasiswa.nama << endl;
		data << perpus[i].mahasiswa.nim << endl;
		data << perpus[i].mahasiswa.jurusan << endl;
		data << perpus[i].judul << endl;
		data << perpus[i].kode << endl;
		data << perpus[i].pinjam << endl;
		data << perpus[i].pengembalian << endl;
	}
	data.close();
}

void binary(int &jmlData, buku perpus[]){
	int i, j, k;
	string cariNama;
	bool found = false;
	cout << "\n-----------------------------------\n";
	cout << "\nMasukkan nama yang dicari : "; cin.ignore(); getline(cin, cariNama);
	i = 0;
	j = jmlData;
	while((!found) & (i <= j)){
		k = (i + j) / 2;
		if(cariNama == perpus[k].mahasiswa.nama){
			found = true;
		}else if(cariNama < perpus[k].mahasiswa.nama){
			j = k - 1; // i tetap
		}else{
			i = k + 1; // j tetap
		}
	}
	if(found){
		cout << "\nDitemukan pada data peminjam buku ke-" << k+1 << endl;
		cout << "Nama : " << perpus[k].mahasiswa.nama << endl;
		cout << "NIM : " << perpus[k].mahasiswa.nim << endl;
		cout << "Jurusan : " << perpus[k].mahasiswa.jurusan << endl;
		cout << "Judul Buku : " << perpus[k].judul << endl;
		cout << "Kode Buku : " << perpus[k].kode << endl;
		cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[k].pinjam << endl;
		cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[k].pengembalian << endl;
	}else{
		cout << cariNama << " tidak ditemukan" << endl;
	}
}

void readDataMerging(ifstream &dataIn, int &jmlData, buku perpus[], string &myFile){
	label_continue :
	int i = 0;
	cin >> myFile;
	dataIn.open(myFile, ios::in);
	if(dataIn.is_open()){
		while(!dataIn.eof()){
			getline(dataIn, perpus[i].mahasiswa.nama);
			getline(dataIn, perpus[i].mahasiswa.nim);
			getline(dataIn, perpus[i].mahasiswa.jurusan);
			getline(dataIn, perpus[i].judul);
			getline(dataIn, perpus[i].kode);
			getline(dataIn, perpus[i].pinjam);
			getline(dataIn, perpus[i].pengembalian);
			
			i++;
		}
		jmlData = i-1;
		dataIn.close();
		for(int i = 0; i < jmlData ; i++){
			cout << "\nData peminjam buku ke-" << i+1 << endl;
			cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
			cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
			cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
			cout << "Judul Buku : " << perpus[i].judul << endl;
			cout << "Kode Buku : " << perpus[i].kode << endl;
			cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
			cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
		}
	}else{
		cout << "File " << myFile << " tidak ditemukan" << endl;
		dataIn.close();
		goto label_continue;
	}
}

void writeDataMerging(fstream &data, int &jmlData, buku perpus[], string &myFileTransaksi){
	data.open(myFileTransaksi, ios::app | ios::out);
	
	for(int i = 0; i < jmlData; i++){
		data << perpus[i].mahasiswa.nama << endl;
		data << perpus[i].mahasiswa.nim << endl;
		data << perpus[i].mahasiswa.jurusan << endl;
		data << perpus[i].judul << endl;
		data << perpus[i].kode << endl;
		data << perpus[i].pinjam << endl;
		data << perpus[i].pengembalian << endl;
	}
	data.close();
}

void readDataMergingSambung(ifstream &dataIn, int &jmlData, buku perpus[], string &myFileTransaksi){
	label_continue :
	int i = 0;
	dataIn.open(myFileTransaksi, ios::in);
	if(dataIn.is_open()){
		while(!dataIn.eof()){
			getline(dataIn, perpus[i].mahasiswa.nama);
			getline(dataIn, perpus[i].mahasiswa.nim);
			getline(dataIn, perpus[i].mahasiswa.jurusan);
			getline(dataIn, perpus[i].judul);
			getline(dataIn, perpus[i].kode);
			getline(dataIn, perpus[i].pinjam);
			getline(dataIn, perpus[i].pengembalian);
			
			i++;
		}
		jmlData = i-1;
		dataIn.close();
		for(int i = 0; i < jmlData ; i++){
			cout << "\nData peminjam buku ke-" << i+1 << endl;
			cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
			cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
			cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
			cout << "Judul Buku : " << perpus[i].judul << endl;
			cout << "Kode Buku : " << perpus[i].kode << endl;
			cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
			cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
		}
	}else{
		cout << "File " << myFileTransaksi << " tidak ditemukan" << endl;
		dataIn.close();
		goto label_continue;
	}
}

void readDataMergingUrut(fstream &data, ifstream &dataIn, int &jmlData, buku perpus[], string &myFileTransaksi){
	label_continue :
	int i = 0;
	dataIn.open(myFileTransaksi, ios::in);
	if(dataIn.is_open()){
		while(!dataIn.eof()){
			getline(dataIn, perpus[i].mahasiswa.nama);
			getline(dataIn, perpus[i].mahasiswa.nim);
			getline(dataIn, perpus[i].mahasiswa.jurusan);
			getline(dataIn, perpus[i].judul);
			getline(dataIn, perpus[i].kode);
			getline(dataIn, perpus[i].pinjam);
			getline(dataIn, perpus[i].pengembalian);
			
			i++;
		}
		jmlData = i-1;
		dataIn.close();
		
		for(int i=0; i < jmlData-1; i++){
			for(int j=0; j < jmlData-1-i; j++){
				if(perpus[j].mahasiswa.nama > perpus[j+1].mahasiswa.nama){
					temp = perpus[j];
					perpus[j] = perpus[j+1];
					perpus[j+1] = temp;
				}
			}
		}
		for(int i = 0; i < jmlData ; i++){
			cout << "\nData peminjam buku ke-" << i+1 << endl;
			cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
			cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
			cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
			cout << "Judul Buku : " << perpus[i].judul << endl;
			cout << "Kode Buku : " << perpus[i].kode << endl;
			cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
			cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
		}
		
		data.open(myFileTransaksi, ios::trunc | ios::out);
		for(int i = 0; i < jmlData; i++){
			data << perpus[i].mahasiswa.nama << endl;
			data << perpus[i].mahasiswa.nim << endl;
			data << perpus[i].mahasiswa.jurusan << endl;
			data << perpus[i].judul << endl;
			data << perpus[i].kode << endl;
			data << perpus[i].pinjam << endl;
			data << perpus[i].pengembalian << endl;
		}
		data.close();
	}else{
		cout << "File " << myFileTransaksi << " tidak ditemukan" << endl;
		dataIn.close();
		goto label_continue;
	}
}

void splitting(ifstream &dataIn, fstream &data, int &jmlData, buku perpus[]){
	string nim, myFileTransaksi1, myFileTransaksi2;
	for(int i = 0; i < jmlData-1; i++){
		for(int j = 0; j < jmlData-1-i; j++){
			if(perpus[j].mahasiswa.nim > perpus[j+1].mahasiswa.nim){
				temp = perpus[j];
				perpus[j] = perpus[j+1];
				perpus[j+1] = temp;
			}
		}
	}
	
	cout << "\n-----------------------------------\n";
	cout << "Masukkan NIM kurang dari : "; cin >> nim;
	cout << "\nNIM < " << nim << " akan masuk file pertama" << endl;
	cout << "NIM >= " << nim << " akan masuk file kedua" << endl;
	cout << "\n-----------------------------------\n";
	
	int i, j, k;
	bool found = false;
	i = 0;
	j = jmlData;
	while((!found) & (i <= j)){
		k = (i + j) / 2;
		if(nim == perpus[k].mahasiswa.nim){
			found = true;
		}else if(nim < perpus[k].mahasiswa.nim){
			j = k - 1;
		}else{
			i = k + 1;
		}
	}
	int jmlData1 = jmlData;
	jmlData1 -= k;
	
	cout << "Masukkan nama file pertama : "; cin >> myFileTransaksi1;
	data.open(myFileTransaksi1, ios::trunc | ios::out);
	
	for(int i = 0; i < jmlData1; i++){
		data << perpus[i].mahasiswa.nama << endl;
		data << perpus[i].mahasiswa.nim << endl;
		data << perpus[i].mahasiswa.jurusan << endl;
		data << perpus[i].judul << endl;
		data << perpus[i].kode << endl;
		data << perpus[i].pinjam << endl;
		data << perpus[i].pengembalian << endl;
	}
	data.close();
	
	cout << "Masukkan nama file kedua : "; cin >> myFileTransaksi2;
	data.open(myFileTransaksi2, ios::trunc | ios::out);
	
	for(int i = k; i < jmlData; i++){
		data << perpus[i].mahasiswa.nama << endl;
		data << perpus[i].mahasiswa.nim << endl;
		data << perpus[i].mahasiswa.jurusan << endl;
		data << perpus[i].judul << endl;
		data << perpus[i].kode << endl;
		data << perpus[i].pinjam << endl;
		data << perpus[i].pengembalian << endl;
	}
	data.close();
	
	cout << "\n-----------------------------------\n";
	cout << "\nOutput File Pertama" << endl;
	i = 0;
	dataIn.open(myFileTransaksi1, ios::in);
	while(!dataIn.eof()){
		getline(dataIn, perpus[i].mahasiswa.nama);
		getline(dataIn, perpus[i].mahasiswa.nim);
		getline(dataIn, perpus[i].mahasiswa.jurusan);
		getline(dataIn, perpus[i].judul);
		getline(dataIn, perpus[i].kode);
		getline(dataIn, perpus[i].pinjam);
		getline(dataIn, perpus[i].pengembalian);
		
		i++;
	}
	jmlData = 0;
	jmlData = i-1;
	dataIn.close();
	for(int i = 0; i < jmlData ; i++){
		cout << "\nData peminjam buku ke-" << i+1 << endl;
		cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
		cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
		cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
		cout << "Judul Buku : " << perpus[i].judul << endl;
		cout << "Kode Buku : " << perpus[i].kode << endl;
		cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
		cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
	}
	
	cout << "\n\nOutput File Kedua" << endl;
	i = 0;
	dataIn.open(myFileTransaksi2, ios::in);
	while(!dataIn.eof()){
		getline(dataIn, perpus[i].mahasiswa.nama);
		getline(dataIn, perpus[i].mahasiswa.nim);
		getline(dataIn, perpus[i].mahasiswa.jurusan);
		getline(dataIn, perpus[i].judul);
		getline(dataIn, perpus[i].kode);
		getline(dataIn, perpus[i].pinjam);
		getline(dataIn, perpus[i].pengembalian);
		
		i++;
	}
	jmlData = 0;
	jmlData = i-1;
	dataIn.close();
	for(int i = 0; i < jmlData ; i++){
		cout << "\nData peminjam buku ke-" << i+1 << endl;
		cout << "Nama : " << perpus[i].mahasiswa.nama << endl;
		cout << "NIM : " << perpus[i].mahasiswa.nim << endl;
		cout << "Jurusan : " << perpus[i].mahasiswa.jurusan << endl;
		cout << "Judul Buku : " << perpus[i].judul << endl;
		cout << "Kode Buku : " << perpus[i].kode << endl;
		cout << "Tanggal/Bulan/Tahun Pinjam : " << perpus[i].pinjam << endl;
		cout << "Tanggal/Bulan/Tahun Pengembalian : " << perpus[i].pengembalian << endl;
	}
}
