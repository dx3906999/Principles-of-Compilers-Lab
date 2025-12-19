FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list && \
    sed -i 's@//.*security.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list

RUN apt-get update && apt-get -y dist-upgrade && \
    apt-get install -y apt-utils vim gcc g++ build-essential make git uuid-dev libssl-dev pkg-config cmake rapidjson-dev openjdk-17-jdk curl

RUN apt-get install -y lsb-release wget software-properties-common gnupg && \
    bash -c "$(curl -O https://apt.llvm.org/llvm.sh)" && \
    chmod +x llvm.sh && \
    ./llvm.sh 15 && \
    apt-get install -y clang-15 && \
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 2 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 2
    # apt-get install -y openssh-server net-tools && \

RUN cd /tmp && \
    curl -O https://www.antlr.org/download/antlr-4.9.3-complete.jar && \
    mv ./antlr-4.9.3-complete.jar /usr/local/lib/ && \
    echo '' >> ~/.bashrc && \
    echo '# antlr env' >> ~/.bashrc && \
    echo 'export CLASSPATH=".:/usr/local/lib/antlr-4.9.3-complete.jar:$CLASSPATH"' >> ~/.bashrc && \
    echo 'alias antlr4='\''java -Xmx500M -cp "/usr/local/lib/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr.v4.Tool'\' >> ~/.bashrc && \
    echo 'alias grun='\''java -Xmx500M -cp "/usr/local/lib/antlr-4.9.3-complete.jar:$CLASSPATH" org.antlr.v4.gui.TestRig'\' >> ~/.bashrc