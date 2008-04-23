./mico-channel-factory-up > factory.ior
sleep 1
./create-mico-channel `cat factory.ior` > canal.ior &
sleep 2
echo "" 
./hello-consumer `cat canal.ior` &
sleep 2
./hello-supplier `cat canal.ior`
