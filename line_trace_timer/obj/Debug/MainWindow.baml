   M S B A M L   `   `   `  ����K  Gline_trace_timer, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null3clr-namespace:line_trace_timerline_trace_timer  5   	   !    line_trace_timer.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   0localclr-namespace:line_trace_timer     5   	   -   5          � Title$  Timer��5   	   $	��720��6   $
��1280��6$   .��5
      � .+�5   
   (� $��10,10,10,100q�6   .��5      �� -   5         ��Name$ lblTime��5      $��	00:00:000��6%   $��Center=�69   $��Center=�6]   $	��300(�6   $	��Top=�6�   $��2��6�   $
��1413��6�   $	��409��6�   5      (� 5   
   $��10,10,10, 0q�6   $	��700��6'   $	��Top=�64   .��5      �� -   5        $ setReady��5      $��READY��6&   $��Center=�66   $��Center=�6Z   $	��160(�6|   $	��Top=�6�   $��1��6�   $
��1413��6�   $	��237��6�   
���  ��$��	Meiryo UI)�6�   5      (� 5   
   $��10,0,10,105q�6   $��58��6'   $��Bottom=�63   .��5      �� -   5        $ 
debugPrint��5      $��READY��6(   $��Center=�68   $��Center=�6\   $	��160(�6~   $	��Top=�6�   $��1��6�   $
��1413��6�   $	��237��6�   
����  �$��	Meiryo UI)�6�   5      A� 5   
   $	��100��6   $��Bottom=�6#    A� Columns$ 3��6>   .+�5      �� -   5         ��Name$ btnStart��5      $��Start��6'   67   �� 5      -   5        $ btnStop��5      $
��Stop��6&   65   �� 5      -   5        $ btnReset��5      $��Reset��6'   67   5      �� 5   
   -   5         ��Name$ textBoxDebug��5      $
��Left=�6*   $��-184,423,0,0q�6E   $
��Wrap=�6[   $��	TextBlock��6o   $	��Top=�6�   $��55��6�   $	��400��6�   5      5      