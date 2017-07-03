FROM ubuntu:16.04
MAINTAINER Roland Kluge
# 'Install' add-apt-repository for TU Design ( http://exp1.fkp.physik.tu-darmstadt.de/tuddesign/)
RUN apt-get update
RUN apt-get install --yes sudo software-properties-common python-software-properties
RUN add-apt-repository "deb http://exp1.fkp.physik.tu-darmstadt.de/tuddesign/ lenny tud-design"
RUN apt-get --allow-unauthenticated update
RUN apt-get install --yes --allow-unauthenticated debian-tuddesign-keyring
RUN apt-get --allow-unauthenticated update 
# Install utilities 
# * 7z: encrypted archive
# * build-essential: make, gcc,... 
# * llvm: clang; 
# * texlive: prerequisiste for tudesign 
# * git (for Docker)
# * after 'git' extra dependencies for latex-tudesign
RUN apt-get install --yes p7zip-full build-essential clang-3.8 texlive-base-bin texlive-science tex-common xfonts-utils latexmk git fonts-cabin fonts-comfortaa fonts-crosextra-caladea fonts-crosextra-carlito fonts-dejavu-extra fonts-ebgaramond fonts-ebgaramond-extra fonts-font-awesome fonts-freefont-otf fonts-freefont-ttf fonts-gfs-artemisia  fonts-gfs-complutum fonts-gfs-didot fonts-gfs-neohellenic fonts-gfs-olga fonts-gfs-solomos fonts-junicode fonts-linuxlibertine fonts-lobster fonts-lobstertwo fonts-oflb-asana-math fonts-roboto-hinted fonts-sil-gentium fonts-sil-gentium-basic fonts-sil-gentiumplus fonts-stix fonts-texgyre preview-latex-style tex-gyre texlive-fonts-extra texlive-fonts-extra-doc texlive-fonts-recommended texlive-fonts-recommended-doc texlive-lang-german texlive-latex-extra texlive-latex-extra-doc tipa ttf-adf-accanthis ttf-adf-gillius ttf-adf-universalis
