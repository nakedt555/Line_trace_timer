   M S B A M L   `   `   `  ����K  Gline_trace_timer, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null3clr-namespace:line_trace_timerline_trace_timer  5   	   '    !line_trace_timer.selectSerialPort   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   0localclr-namespace:line_trace_timer     5   	     � 
ResizeMode$  NoResize=�5   	    � Title$ selectSerialPort��5	   	   $��171.535��6"   $��412.129��63   .��5
      � .+�5   
   �� 
���   �$��1q�6%   $
��Left=�69   $��76��6T   $��	10,10,0,0q�6`   $	��Top=�6s   $	��377��6�   �� 5   
   $
��Left=�6   $��	24,18,0,0q�6/   $
��Wrap=�6B   $��COMポート��6V   $	��Top=�6d   $��22��6|   $��14(�6�   �� 5   
   -   5         ��Name$ SerialComPort��5      $
��Left=�6*   $��	98,18,0,0q�6E   $	��Top=�6X   $	��281��6p   �� 5   
   $
��Left=�6   $��	24,54,0,0q�6/   $
��Wrap=�6B   $��ボーレート��6V   $	��Top=�6c   $��22��6{   $��14(�6�   �� 5   
   -   5        $ SerialBaudRate��5      $
��Left=�6+   $��	98,54,0,0q�6F   $	��Top=�6Y   $	��281��6q   �� 5   
   -   5         ��Name$ SerialStartBtn��5      $��開始��6)   $
��Left=�66   $��
98,101,0,0q�6Q   $	��Top=�6e   $��75��6}   $��14(�6�    J� RenderTransformOrigin$ 0.643,0.396&�6�   6�   �� 5   
   -   5        $ SerialCancelBtn��5      $��キャンセル��6*   $
��Left=�6:   $��258,101,0,0q�6U   $	��Top=�6j   $��75��6�   $��14(�6�   $ 0.643,0.396&�6�   6�   �� 5   
   -   5        $ SerialUpdadteBtn��5      $��更新��6+   $
��Left=�68   $��178,101,0,0q�6S   $	��Top=�6h   $��75��6�   $��14(�6�   $ 0.643,0.396&�6�   6�   5      5      