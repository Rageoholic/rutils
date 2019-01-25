/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"

#define _XOPEN_SOURCE 1000
#pragma clang diagnostic pop

#include "network.h"
#include <stdio.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <assert.h>

#define SOCKADDR_LENGTH_DEFAULT sizeof(struct sockaddr_storage)

local int ReadFlagsToRecvFlags(ReadFlags flags)
{
    int recvFlags = 0;
    if (flags & READ_PEEK)
    {
        recvFlags |= MSG_PEEK;
    }
    if (flags & READ_NO_BLOCK)
    {
        recvFlags |= MSG_DONTWAIT;
    }
    return recvFlags;
}

local int RoleToAIFlags(Role role)
{
    if (role == SERVER)
    {
        return AI_PASSIVE;
    }
    else
    {
        return 0;
    }
}

local int ConnTypeToSockType(ConnType connType)
{
    if (connType == TCP)
    {
        return SOCK_STREAM;
    }
    else
    {
        return SOCK_DGRAM;
    }
}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-align"

local void *GetInAddr(_SockAddr *sa)
{
    assert(sa != NULL);
    if (((struct sockaddr *)sa)->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    else
    {
        return &(((struct sockaddr_in6 *)sa)->sin6_addr);
    }
}
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
typedef struct
{
    Socket s;
    AddrInfo p;
} AITSTuple;
#pragma clang diagnostic pop

local AITSTuple AddrInfoToSocket(AddrInfo a)
{

    for (AddrInfo p = a; p != NULL; p = NextAddrInfo(p))
    {
        int sock;
        if ((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {

            perror("AddrInfoToSocket: socket");
            continue;
        }
        AITSTuple ret = {{sock}, p};
        return ret;
    }
    AITSTuple ret = {{-1}, NULL};
    return ret;
}

TCPSocket CreateTCPServerSocket(const char *port, int connBacklog)
{
    AddrInfo servInfo;

    TCPSocket inval = {-1};
    int rv;
    if ((rv = GetAddrInfo(SERVER, TCP, NULL, port, &servInfo)) != 0)
    {
        fprintf(stderr, "%s\n", GaiError(rv));

        return inval;
    }

    Socket sock = BindToAddrInfo(servInfo);
    if (sock._s == -1)
    {
        return inval;
    }
    DestroyAddrInfo(servInfo);

    TCPSocket tsock = sock;
    if (ListenToTCPSocket(tsock, connBacklog) == -1)
    {
        perror("CreateTCPServerSocket");
        DestroySocket(sock);
        return inval;
    }
    return tsock;
}

TCPSocket CreateTCPClientSocket(const char *name, const char *port,
                                AddrInfo *givenServInfo)
{
    AddrInfo altServInfo = NULL;

    AddrInfo *servInfo;
    if (givenServInfo == NULL)
    {
        servInfo = &altServInfo;
    }
    else
    {
        servInfo = givenServInfo;
    }
    int rv;
    if ((rv = GetAddrInfo(CLIENT, TCP, name, port, servInfo)) != 0)
    {
        fprintf(stderr, "%s\n", GaiError(rv));
        TCPSocket inval = {-1};
        return inval;
    }

    TCPSocket sock = ConnectToTCPSocket(*servInfo);
    if (altServInfo != NULL)
    {
        DestroyAddrInfo(altServInfo);
    }
    return sock;
}

UDPListenerSocket CreateUDPListenerSocket(const char *port)
{
    AddrInfo servInfo;

    int rv;
    if ((rv = GetAddrInfo(SERVER, UDP, NULL, port, &servInfo)) != 0)
    {
        fprintf(stderr, "%s\n", GaiError(rv));
        UDPListenerSocket inval = {-1};
        return inval;
    }

    UDPListenerSocket sock = BindToAddrInfo(servInfo);
    DestroyAddrInfo(servInfo);
    return sock;
}

UDPTalkerSocket CreateUDPTalkerSocket(const char *name, const char *port,
                                      SockAddr *theirAddr)
{
    assert(theirAddr != NULL);

    AddrInfo servInfo;
    int rv;
    if ((rv = GetAddrInfo(CLIENT, UDP, name, port, &servInfo)) != 0)
    {
        fprintf(stderr, "%s\n", GaiError(rv));
        UDPTalkerSocket inval = {-1};
        return inval;
    }

    AITSTuple udpconn = AddrInfoToSocket(servInfo);
    assert(udpconn.p != NULL);
    theirAddr->_len = udpconn.p->ai_addrlen;
    theirAddr->_s = malloc(theirAddr->_len);
    memcpy(theirAddr->_s, udpconn.p->ai_addr, theirAddr->_len);

    DestroyAddrInfo(servInfo);
    UDPTalkerSocket s = udpconn.s;
    return s;
}

int GetAddrInfo(Role role, ConnType connType, const char *name,
                const char *port, AddrInfo *res)
{
    _AddrInfo hints = {.ai_flags = RoleToAIFlags(role),
                       .ai_family = AF_UNSPEC,
                       .ai_socktype = ConnTypeToSockType(connType)};

    return getaddrinfo(name, port, &hints, res);
}

const char *GaiError(int errcode)
{
    return gai_strerror(errcode);
}

AddrInfo NextAddrInfo(AddrInfo a)
{
    return a->ai_next;
}

Socket BindToAddrInfo(AddrInfo a)
{
    for (AddrInfo p = a; p != NULL; p = NextAddrInfo(p))
    {
        Socket sock = {socket(p->ai_family, p->ai_socktype, p->ai_protocol)};
        if (sock._s == -1)
        {
            perror("socket");
            continue;
        }
        int yes = 1;
        if (setsockopt(sock._s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sock._s, p->ai_addr, p->ai_addrlen) == -1)
        {
            DestroySocket(sock);
            perror("bind");
            continue;
        }

        return sock;
    }
    /* Error case */
    Socket inval = {-1};
    return inval;
}

int ListenToTCPSocket(TCPSocket sock, int connBacklog)
{
    if (listen(sock._s, connBacklog) == -1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

TCPSocket ConnectToTCPSocket(AddrInfo a)
{
    for (AddrInfo p = a; p != NULL; p = NextAddrInfo(p))
    {
        TCPSocket sock = {socket(p->ai_family, p->ai_socktype, p->ai_protocol)};
        if (sock._s == -1)
        {
            perror("ConnectToSocket: socket");
            continue;
        }

        if (connect(sock._s, p->ai_addr, p->ai_addrlen) == -1)
        {
            DestroySocket(sock);
            perror("ConnectToSocket: connect");
            continue;
        }

        return sock;
    }
    TCPSocket inval = {-1};
    return inval;
}

IpVer GetIpVer(AddrInfo a)
{
    return (a->ai_family == AF_INET) ? IPV4 : IPV6;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-align"

const char *GetIpStr(AddrInfo a, char *ipstr, size_t ipstrLength)
{
    void *addr;

    if (GetIpVer(a) == IPV4)
    {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)a->ai_addr;
        addr = &(ipv4->sin_addr);
    }
    else
    {
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)a->ai_addr;
        addr = &(ipv6->sin6_addr);
    }

    return inet_ntop(a->ai_family, addr, ipstr, (socklen_t)ipstrLength);
}
#pragma clang diagnostic pop
void DestroyAddrInfo(AddrInfo a)
{
    freeaddrinfo(a);
}

TCPSocket AcceptConnection(TCPSocket sock, SockAddr *theirAddr)
{
    if (theirAddr != NULL && theirAddr->_s == NULL)
    {
        /* Initialize the theirAddr. */

        theirAddr->_s = malloc(sizeof(struct sockaddr_storage));
        theirAddr->_len = SOCKADDR_LENGTH_DEFAULT;
    }

    _SockAddr *a = theirAddr ? theirAddr->_s : NULL;

    socklen_t addrLen = theirAddr ? SOCKADDR_LENGTH_DEFAULT : 0;
    TCPSocket r = {accept(sock._s, a, &addrLen)};
    return r;
}

const char *SockAddrToStr(SockAddr *addr, char *dst)
{
    return inet_ntop(addr->_s->sa_family, GetInAddr(addr->_s), dst, (socklen_t)addr->_len);
}

int DestroySocket(Socket sock)
{
    return close(sock._s);
}

isize TCPSendData(TCPSocket sock, const void *buf, size_t len)
{
    return send(sock._s, buf, len, 0);
}

isize TCPRecvData(TCPSocket sock, void *buf, size_t len, ReadFlags flags)
{
    return recv(sock._s, buf, len, ReadFlagsToRecvFlags(flags));
}

isize UDPRecvData(UDPListenerSocket sock, void *buf, size_t len, ReadFlags flags,
                  SockAddr *theirAddr)
{

    if (theirAddr && !theirAddr->_s)
    {

        theirAddr->_s = malloc(sizeof(struct sockaddr_storage));

        theirAddr->_len = sizeof(struct sockaddr_storage);
    }
    _SockAddr *lTheirAddr = theirAddr ? theirAddr->_s : NULL;

    socklen_t socklen = theirAddr ? (socklen_t)theirAddr->_len : 0;
    isize ret = recvfrom(sock._s, buf, len, ReadFlagsToRecvFlags(flags), lTheirAddr, &socklen);

    return ret;
}

isize UDPSendData(UDPTalkerSocket sock, const void *buf, size_t len, SockAddr s)
{
    return sendto(sock._s, buf, len, 0, s._s, (socklen_t)s._len);
}

void PrintError(char *error)
{
    perror(error);
}

void DestroySockAddr(SockAddr s)
{
    free(s._s);
}
bool IsValidSocket(Socket sock)
{
    return sock._s != -1;
}
