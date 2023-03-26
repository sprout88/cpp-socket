#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // 파일 관리 함수 헤더
#include <arpa/inet.h>
#include <sys/socket.h> // 소켓프로그래밍 함수선언
#define PORT 81
void errhandle(char *errmsg){
	fputs(errmsg, stderr);
    fputc('\n', stderr);
    exit(1);
}
 
int main(){
    std::cout<<"server start!!"<<std::endl;
    // 서버, 클라이언트 소켓 파일디스크립터 변수 선언
	int serv_sock, clnt_sock;
    
    // sockaddr_in 구조체 변수 선언
    struct sockaddr_in st_serv_addr;
    struct sockaddr_in st_clnt_addr;
    
    // 보내고 받을 버퍼 정의
    char sendmsg[] = "Test";
    char recvmsg[1024];
    
    // ip, port 정의
    char ip[] = "127.0.0.1"; //
    int port = PORT;
    
    // 서버 소켓 TCP/IP 프로토콜 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        errhandle("socket() ERR!");
    }

    // serv_sock에 bind로 주소 넣기 위한 밑작업
    memset(&st_serv_addr,0,sizeof(st_serv_addr));
    st_serv_addr.sin_family = AF_INET;
    st_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    st_serv_addr.sin_port = htons(port);
    
    // bind()로 서버 소켓에 주소정보 할당
    int bindret = bind(serv_sock, (struct sockaddr*) &st_serv_addr, sizeof(st_serv_addr) );

    // if(bindret == -1){
    //     errhandle("bind() ERR!");
    // }

    // listen()으로 서버소켓으로 오는 클라이언트 요청 대기
    int listenret = listen(serv_sock,10);
    if(listenret == -1) errhandle("listen() ERR!");
    
    // accept 하기위한 클라이언트 구조체 크기 밑작업 및 함수호출
    int clnt_addr_size = sizeof(st_clnt_addr);
    int acceptret = accept(serv_sock,(struct sockaddr*) &st_clnt_addr, (socklen_t*)&clnt_addr_size );
    if(acceptret == -1) errhandle("accept() ERR!");
    
    // sendmsg 보내고, recvmsg에 수신된 string데이터 담기
    write(clnt_sock, sendmsg, sizeof(sendmsg) );
    int readstrlen = read(clnt_sock, recvmsg, sizeof(recvmsg)-1);
    
    //소켓은 파일이다! 닫아야 한다.
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
    }