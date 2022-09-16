
# USB Relay Module comands
alias getrelay='<INSERT PATH TO URM BINARIES>/getrelay'
alias setrelay='<INSERT PATH TO URM BINARIES>/setrelay'
alias target-on='setrelay R1_2=0'
alias target-off='setrelay R1_2=1'
alias target-reset='target-off && sleep 5s && target-on'