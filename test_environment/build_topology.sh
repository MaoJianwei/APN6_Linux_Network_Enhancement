ip netns add MaoClient
ip netns add MaoServer

# Client-Server
ip link add ClientEth1 type veth peer name ServerEth1
ip link set ClientEth1 netns MaoClient
ip link set ServerEth1 netns MaoServer

ip netns exec MaoClient ip link set ClientEth1 up
ip netns exec MaoClient ip addr add 2001:da8:215:A::AAAA/64 dev ClientEth1

ip netns exec MaoServer ip link set ServerEth1 up
ip netns exec MaoServer ip addr add 2001:da8:215:A::BBBB/64 dev ServerEth1

sleep 3

ip netns exec MaoClient ping -c 1 2001:da8:215:A::BBBB
