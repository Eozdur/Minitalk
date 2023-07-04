/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <eozdur@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:12:17 by eozdur            #+#    #+#             */
/*   Updated: 2023/07/05 01:40:51 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Minitalk projesi client'dan okunan mesajı server'a PID sinyallerini kullanarak göndericeğiz ve yazdıracağız
#include "minitalk.h"

//pid(process id 'yi) int'e çevirmek için atoi kullandık
int	ft_atoi(char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && str[i])
	{
		res = (str[i] - 48) + (res * 10);
		i++;
	}
	return (res * s);
}
/*	
yazılan mesajı direk string olarak atamıyoruz o yüzden harf harf atıcaz bu harfleride byte byte
atıcaz ve bu bytelarıda bit bit okumamız lazım 1byte = 8 bit
*/
void	ft_send_signal(int pid, char *str)
{
	int				i;
	unsigned char	c;

	// girilen mesaj bitene kadar mesajı göndermeye devam eder
	while (*str)
	{
		i = 8;
		// burada str'yi c ye atar (mesajımız "emre" olsun e'yi c ye atar)
		// ++ ile strnin tuttuğu yer artık "m" olur ve "mre" yi gösterir
		c = *str++;
		while (i--)
		{
			// c yi i kadar sağa kaydırma yapar örn = e nin 2 lik karşılığı 01100101
			// bunu i kadar sağa ötele i=7 00000000 | i=6 00000001 | i=5 000000011 
			// i-- ile i= 7,6,5,4,3... gönderilir böylece bit kaybı olmaz 
			// ve and ile 1 veya 0 durumuna göre SİGUSR1(1) veya SİGUSR2(0) ye gönderir
			//böyle böyle harf*8 bit gönderince bit_write ile 8 bite karşılık gelen harfi yazdırır
			if ((c >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
				// 100 ms gecikme yapıyoruz ki sinyaller karışmasın
			usleep(100);
		}
	}
}

int	main(int argc, char *argv[])
{
	int	pid;
	// eğer argüman sayısı  3 değilse (yani ./client pid "mesaj" şeklinde girilmemiş ise)
	if (argc != 3)
	{
		ft_printf("Hatali giris ! 3 argüman girmelisin !");
		return (0);
	}
	pid = ft_atoi(argv[1]);
	//server'a göndereceğimiz mesajı ve pid numaramızı fonksiyona yolluyoruz
	ft_send_signal(pid, argv[2]);
}
