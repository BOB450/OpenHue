# Maintainer: Your Name <bwvoskuil@gmail.com to contact BOB4500@protonmail.com>
pkgname=OpenHue
pkgver=0.4
pkgrel=1
pkgdesc="A desktop application to controll philips hue compatable smart bulbs."
arch=()
url=""
license=('GPL')
groups=()
depends=()
makedepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=($pkgname-$pkgver.tar.gz)
noextract=()
md5sums=() #autofill using updpkgsums

build() {
  cd "$pkgname-$pkgver"

  ./configure --prefix=/usr
  make
}

package() {
  cd "$pkgname-$pkgver"

  make DESTDIR="$pkgdir/" install
}
