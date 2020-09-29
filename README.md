[![Contributors][contributors-shield]][contributors-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
[![Website][website-shield]][website-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
<!--  
 <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
 -->
  <h3 align="center">ZeOS</h3>

  <p align="center">
    A basic, fully-functional operating system on command line.
  </p>
</p>


<!-- About the project -->
## 😎 About
Project made for Operating Systems course of FIB - UPC. 
It is a fully working operating system with basic system calls that runs on an emulator.
Feel free to try it!


<!-- GETTING STARTED -->
## 👉🏽 Getting Started

### Prerequisites
Make sure to install everything:
- [Bochs](http://bochs.sourceforge.net/)

### Installation

1. Clone this repository
```sh
git clone https://github.com/matiszz/ZeOS.git
cd ZeOS/
```

1. Generate `zeos.bin` executable.
```sh
make
```
2. Test ZeOS without a debugger.
```sh
make emul
```
3. Test ZeOS on a debugging environment.
```sh
bochs -q
```



<!-- LICENSE -->
## 📚 License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## 📞 Contact

Matias Szarfer - 🐤 [@matiasszarfer](https://twitter.com/matiasszarfer) · 📧 matias@szarfer.com · 💻 [matias.szarfer.com](https://matias.szarfer.com)

Project Link: [https://github.com/matiszz/ZeOS.git](https://github.com/matiszz/ZeOS.git)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=flat-square
[contributors-url]: https://github.com/matiszz/ZeOS/graphs/contributors

[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=flat-square
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/matias-szarfer

[website-shield]: https://img.shields.io/badge/-Website-black.svg?style=flat-square&colorB=555
[website-url]: https://matias.szarfer.com