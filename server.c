/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:12:01 by eozdur            #+#    #+#             */
/*   Updated: 2023/07/05 01:41:33 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// gelen bitleri teker teker tutuyor ve 8 bit olunca oluşan harfi yazdırıyor
void	ft_bit_write(int x)
{
	static int	bit = 7;
	static int	set = 0;

	// ilk çağırıldığında örn: e = 01100101 ilk olarak client'den en soldaki 0 geldi
	// yani x=0 bit=7 oldu 0<<7 = 0 oldu bitimiz bir azaldı ve bir sağa kaydı değerimiz 1 oldu
	// x=1 bit=6 1<<6=64 oldu bit 0 olana kadar gelen değerleri toplayıp set'e atıyoruz  
	// e için setin değeri 101 gelicek ve bu değeride printf fonksiyonunda %c ile harfi yazdırıyoruz.
	// değerleri sıfırlıyoruz çünkü 2. harf için aynı işlemleri tekrar edicek.
	set += (x << bit);
	if (bit == 0)
	{
		ft_printf("%c", set);
		bit = 7;
		set = 0;
	}
	else
		bit--;
}

void	ft_signal_control(int x)
{
	if (x == SIGUSR1)
	// 1 gelirse 1 gönder
		ft_bit_write(1);
	else
	// 0 gelirse 0 gönder 
		ft_bit_write(0);
}

int	main(void)
{
	int	pid;
	// pid numaramızı pid değişkenimize atadık
	pid = getpid();
	ft_printf("Pid--> %u\n", pid);//ekrana pid yazdırdık böylece hangi pid numarasına gönderme yapacağım belli
	//sigusr1'den sinyal gelirse 2. parametreyi fonksiyona sokuyor
	signal(SIGUSR1, ft_signal_control);
	signal(SIGUSR2, ft_signal_control);
	// sonsuz döngüye sokuyoruz böylece sınırsız sayıda mesaj girebiliyoruz
	// ve yukarıdaki fonksiyonlar sürekli sinyal bekliyor.
	while (1)
	// programımız bitmesin diye sürekli pause verip sinyaller için bekletiyoruzs
		pause();
}

